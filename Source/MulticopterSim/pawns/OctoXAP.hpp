/*
 Vehicle class or octo-X frames using ArduPilot motor layout:

        5CCW  1CW
               
    7CW          3CCW
               
            ^     
               
    6CW          8CCW
               
        2CCW  4CW

 Copyright (C) 2019 Simon D. Levy, Daniel Katzav

 MIT License
*/

#pragma once

#include "Vehicle.hpp"
#include "dynamics/QuadXAP.hpp"

class OctoXAP : public Vehicle {

    public:	

        // XXX Use QuadXAP dynamics for now
        OctoXAP(const objects_t & objects, const MultirotorDynamics::params_t & params) : Vehicle(objects, new QuadXAPDynamics(params))
        {
        }

}; // class OctoXAP
