/*
   Event camera simulation thread

   Copyright(C) 2019 Simon D.Levy

   MIT License
*/

#pragma once

#include "../MainModule/ThreadedManager.hpp"
#include "TargetPawn.h"

class FEventCameraManager : public FThreadedManager {

    private:

        class AEventCameraPawn * _vehiclePawn = NULL;
        class ATargetPawn * _targetPawn = NULL;

    public:

        FEventCameraManager(class AEventCameraPawn * vehiclePawn, class ATargetPawn * targetPawn)
            : FThreadedManager()
        {
            _vehiclePawn = vehiclePawn;
            _targetPawn  = targetPawn;
        }

        void performTask(double currentTime)
        {
            debug("%p %p", _vehiclePawn, _targetPawn);
        }
}; 
