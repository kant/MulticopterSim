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

        protected:

            virtual bool modifyDemands(state_t & state, demands_t & demands, float currentTime) override
            {
                demands.throttle = 1.0;

                return true;
            }


        public:

            NengoAltitudeHold(float Kp, float Kd)
            {
                _pidController = new NengoPidController(Kp, Kd);
            }

    }; // class NengoAltitudeHold

}  // namespace hf
