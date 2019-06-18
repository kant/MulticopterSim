/*
   Hackflight Altitude hold PID class using Nengo PID controller

   Copyright(C) 2019 Simon D.Levy

   MIT License
   */

#pragma once

#include <pidcontroller.hpp>

#include "NengoPidController.hpp"

namespace hf {

    class NengoAltitudeHold : public hf::PID_Controller {
        
        private:

            NengoPidController * _pidController;

            // Arbitrary constants
            const float WINDUP_MAX      = 0.40f;
            const float HOVER_THROTTLE  = 0.05f;

            // Minimum altitude, set by constructor
            float _minAltitude = 0;

            // PID constants set by constructor
            float _posP = 0;
            float _velP = 0;
            float _velI = 0;
            float _velD = 0;

            // Parameter to avoid integral windup
            float _windupMax = 0;

            // Values modified in-flight
            float _posTarget = 0;
            bool  _inBandPrev = false;
            float _lastError = 0;
            float _integralError = 0;
            float _altitudeTarget = 0;
            float _previousTime = 0;

            bool inBand(float demand)
            {
                return fabs(demand) < Receiver::STICK_DEADBAND; 
            }

            void resetErrors(void)
            {
                _lastError = 0;
                _integralError = 0;
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
                    resetErrors();
                }
                _inBandPrev = inBandCurr;

                if (!inBandCurr) return false;

                // Compute control correction
                correction = 1.0f;

                return true;
            }

        protected:

            virtual bool modifyDemands(state_t & state, demands_t & demands, float currentTime) override
            {

                // Don't do anything till we've reached sufficient altitude
                if (state.location[2] < _minAltitude) return false;

                float correction = 0;
                if (gotCorrection(demands.throttle, state.location[2], state.inertialVel[2], currentTime, correction)) {
                    demands.throttle = correction + HOVER_THROTTLE;
                    return true;
                }

                return false;
            }


        public:

            NengoAltitudeHold(float Kp, float Kd)
            {
                _pidController = new NengoPidController(Kp, Kd);
            }

    }; // class NengoAltitudeHold

}  // namespace hf
