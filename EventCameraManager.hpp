/*
   Event camera simulation thread

   Copyright(C) 2019 Simon D.Levy

   MIT License
*/

#pragma once

#include "../MainModule/ThreadedManager.hpp"
#include "TargetPawn.h"
#include "Davis346Sim.hpp"

class FEventCameraManager : public FThreadedManager {

    private:

        APawn * _vehiclePawn = NULL;
        ATargetPawn * _targetPawn = NULL;

        Davis346 davis;

        static FVector getLocation(APawn * pawn)
        {
            return pawn->GetActorLocation() / 100; // cm => m
        }

    public:

        FEventCameraManager(APawn * vehiclePawn, ATargetPawn * targetPawn)
            : FThreadedManager()
        {
            _vehiclePawn = vehiclePawn;
            _targetPawn  = targetPawn;
        }

        void performTask(double currentTime)
        {
			FVector vehicleLocation = getLocation(_vehiclePawn);
			FVector targetLocation = getLocation(_targetPawn);
            FBox targetBox = _targetPawn->getBoundingBox();
            FVector targetSize = targetBox.GetSize() / 100;

			debug("vehicle: %+3.3f %+3.3f %+3.3f    target: %+3.3f %+3.3f %+3.3f size = %3.3f %3.3f %3.3f",
				vehicleLocation.X, vehicleLocation.Y, vehicleLocation.Z,
				targetLocation.X, targetLocation.Y, targetLocation.Z,
                targetSize.X, targetSize.Y, targetSize.Z);
        }
}; 
