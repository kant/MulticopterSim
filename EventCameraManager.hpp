/*
   Event camera simulation thread

   Copyright(C) 2019 Simon D.Levy

   MIT License
*/

#pragma once

#include "../MainModule/ThreadedWorker.hpp"

class FEventCameraManager : public FThreadedWorker {

    private:

        APawn * _vehiclePawn = NULL;
        APawn * _targetPawn = NULL;

    public:

        FEventCameraManager(APawn * vehiclePawn, APawn * targetPawn)
        {
            _vehiclePawn = vehiclePawn;
            _targetPawn  = targetPawn;
        }

        void performTask(double currentTime)
        {
        }
}; 
