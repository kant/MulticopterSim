/*
   MulticopterSim FlightManager class implementation using a simple takeoff-and-hold PID controller

   Copyright(C) 2019 Simon D.Levy

   MIT License
*/

#include "../MainModule/FlightManager.hpp"
#include "../MainModule/Debug.hpp"

class FNullFlightManager : public FFlightManager {

    private:

        // Target 
        static constexpr double ALTITUDE_TARGET = 10;

        // PID params
        static constexpr double ALT_P = 1.0; // Altitude set-point
        static constexpr double VEL_P = 1.0; // Climb rate

        // PID controller support
        double _zprev = 0;
        double _tprev = 0;
        double _lastError = 0;

        // helpers
        static double max(double a, double b) { return a > b ? a : b; }
        static double min(double a, double b) { return a < b ? a : b; }

    public:

        // Constructor
        FNullFlightManager(MultirotorDynamics * dynamics, FVector initialLocation, FRotator initialRotation) 
            : FFlightManager(dynamics, initialLocation, initialRotation) 
        {
            // initial conditions
            _zprev = 0;
            _tprev = 0;
            _lastError = 0;
        }

        virtual ~FNullFlightManager(void)
        {
        }

        virtual void getMotors(const double time, const MultirotorDynamics::state_t & state, double * motorvals) override
        {

            // Extract altitude from state.  Altitude is in NED coordinates, so we negate it to use as input
            // to PID controller.
            double z = -state.pose.location[2];

            double u = 0;

            // Compute vertical climb rate as first difference of altitude over time
            if (time > _tprev) {

                // Use temporal first difference to compute vertical velocity
                double dt = time - _tprev;
                double dzdt = (z-_zprev) / dt;

                // Run the PID controller
                double velTarget = (ALTITUDE_TARGET - z) * ALT_P;
                double velError  = velTarget - dzdt;
                double deltaError = 0;
                u = VEL_P * velError;

                // Constrain correction to [0,1] to represent motor value
                u = max(0, min(1, u));  

                // Pause briefly to yield to other threads
                FPlatformProcess::Sleep(0.001);
            }

            // Update for first difference
            _zprev = z;
            _tprev = time;    

            // Set all motors based on the PID controller value
            for (uint8_t k=0; k<_motorCount; ++k) {
                motorvals[k] = u;
            }

        }

}; // NullFlightManager


// Factory method for FlightManager class
FLIGHTMODULE_API FFlightManager * createFlightManager(MultirotorDynamics * dynamics, FVector initialLocation, FRotator initialRotation)
{
    return new FNullFlightManager(dynamics, initialLocation, initialRotation);
}
