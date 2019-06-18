/*
   Hackflight Altitude hold PID class using Nengo PID controller

   Copyright(C) 2019 Simon D.Levy

   MIT License
   */

#pragma once

// Hackflight
#include <pidcontroller.hpp>

// MulticopterSim
#include <Debug.hpp>

// SimPlugin
#include "NengoPidController.hpp"

namespace hf {

    class NengoAltitudeHold : public hf::PID_Controller {
        
        private:

            NengoPidController * _pidController;

            // Constants
            static constexpr float KP = 1.00;
            static constexpr float KD = 0.00;
            static constexpr float KI = 0.00;
            static constexpr float SIM_TIME = 0.001;
            static const     int   N_NEURONS = 100;

            // Minimum altitude, set by constructor
            float _minAltitude = 0;

            // Values modified in-flight
            float _posTarget = 0;
            bool  _inBandPrev = false;
            float _altitudeTarget = 0;
            float _previousTime = 0;

            bool inBand(float demand)
            {
                return fabs(demand) < Receiver::STICK_DEADBAND; 
            }

            bool gotCorrection(float demand, float posActual, float velActual, float currentTime, float & correction)
            {
                // Don't do anything until we have a positive deltaT
                float deltaT = currentTime - _previousTime;

                _previousTime = currentTime;
                if (deltaT == currentTime) return false;

                // Reset target if moved into stick deadband
                bool inBandCurr = inBand(demand);
                if (inBandCurr && !_inBandPrev) {
                    _posTarget = posActual;
                }
                _inBandPrev = inBandCurr;

                if (!inBandCurr) return false;

                // Compute control correction
                _pidController->getCorrection(&_posTarget, &posActual, &correction);

                return true;
            }

        protected:

            virtual bool modifyDemands(state_t & state, demands_t & demands, float currentTime) override
            {

                // Don't do anything till we've reached sufficient altitude
                if (state.location[2] < _minAltitude) return false;

                float correction = 0;
                if (gotCorrection(demands.throttle, state.location[2], state.inertialVel[2], currentTime, correction)) {
                    demands.throttle += correction;
                    return true;
                }

                return false;
            }


        public:

            NengoAltitudeHold(void)
            {
                debug("Starting Nengo ...");

                _pidController = new NengoPidController(KP, KD, KI, 1, SIM_TIME, N_NEURONS);
             }

    }; // class NengoAltitudeHold

}  // namespace hf
