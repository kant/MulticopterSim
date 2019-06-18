/*
   MulticopterSim FlightManager class implementation using Hackflight

   Just spins propellers

   Copyright(C) 2019 Simon D.Levy

   MIT License
*/

#include "../MulticopterSim/FlightManager.hpp"

#include "SimBoard.hpp"
#include "SimSensors.hpp"

// Math support
#define _USE_MATH_DEFINES
#include <math.h>

#include <hackflight.hpp>
#include "SimReceiver.hpp"

// standard PID controllers
#include <pidcontrollers/level.hpp>
#include <pidcontrollers/rate.hpp>

// Nengo PID controller for altitude-hold
#include "NengoAltitudeHold.hpp"

// Mixer
#include <mixers/quadxap.hpp>

class FNullFlightManager : public FFlightManager {

    private:

        // PID tuning

        // Rate
        hf::Rate _ratePid = hf::Rate(
                0.01,	// Roll/Pitch P
                0.01,	// Roll/Pitch I
                0.01,	// Roll/Pitch D
                0.025,	// Yaw P
                0.01,	// Yaw I
                8.00);	// Demands to rate

        // Level
        hf::Level _levelPid = hf::Level(0.1);

        // Nengo-based altitude hold
        hf::NengoAltitudeHold * _altitudePid;

        // Main firmware
        hf::Hackflight _hackflight;

        // Flight-controller board
        SimBoard _board;

        // "Receiver" (joystick/gamepad)
        SimReceiver _receiver;

        // Mixer
        hf::MixerQuadXAP _mixer;

        // "Sensors" (get values from dynamics)
        SimSensors * _sensors = NULL;

        // Gimbal axes
        float _gimbalRoll = 0;
        float _gimbalPitch = 0;
        float _gimbalFOV = 0;

    public:

        // Constructor
        FNullFlightManager(MultirotorDynamics * dynamics, FVector initialLocation, FRotator initialRotation) 
            : FFlightManager(dynamics, initialLocation, initialRotation) 
        {
            // Start Hackflight firmware, indicating already armed
            _hackflight.init(&_board, &_receiver, &_mixer, &_ratePid, true);

            // Add simulated sensor suite
            _sensors = new SimSensors(_dynamics);
            _hackflight.addSensor(_sensors);

            // Add level PID controller for aux switch position 1
            _hackflight.addPidController(&_levelPid, 1);

            // Add altitude-hold and position-hold PID controllers in switch position 2
            //_hackflight.addPidController(&althold, 2);    

            // Start gimbal in center, medium Field-Of-View
            _gimbalRoll = 0;
            _gimbalPitch = 0;
            _gimbalFOV = 90;
         }

        virtual ~FNullFlightManager(void)
        {
            delete _sensors;
        }

        virtual void update(const double time, const MultirotorDynamics::state_t & state, double * motorvals) override
        {
            Joystick::error_t joystickError = _receiver.update();

            switch (joystickError) {

                case Joystick::ERROR_MISSING:
                    dbgprintf("*** NO JOYSTICK DETECTED ***");
                    break;

                case Joystick::ERROR_PRODUCT:
                    dbgprintf("*** JOYSTICK NOT RECOGNIZED ***");
                    break;

                default:

                    if (_receiver.inGimbalMode()) {
                        _receiver.getGimbal(_gimbalRoll, _gimbalPitch, _gimbalFOV);
                    }

                    _hackflight.update();

                    // Input deltaT, quat, gyro; output motor values
                    _board.update(time, state.quaternion, state.angularVel, motorvals);
            }
        }

        virtual void getGimbal(float & roll, float &pitch, float & fov) override
        {
            roll =  _gimbalRoll;
            pitch = _gimbalPitch;
            fov =   _gimbalFOV;
        }

}; // NullFlightManager


// Factory method for FlightManager class
SIMPLUGIN_API FFlightManager * createFlightManager(MultirotorDynamics * dynamics, FVector initialLocation, FRotator initialRotation)
{
    return new FNullFlightManager(dynamics, initialLocation, initialRotation);
}
