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

        Davis346 * _davis = NULL;

        static Davis346::location_t getLocation(APawn * pawn)
        {
            FVector fv = pawn->GetActorLocation() / 100; // cm => m
            Davis346::location_t loc = {fv.X, fv.Y, fv.Z};
            return loc;
        }

    public:

        FEventCameraManager(APawn * vehiclePawn, ATargetPawn * targetPawn)
            : FThreadedManager()
        {
            _vehiclePawn = vehiclePawn;
            _targetPawn  = targetPawn;

            FBox targetBox = _targetPawn->getBoundingBox();
            FVector targetSize = targetBox.GetSize() / 100;

            _davis = new Davis346(targetSize.X); // assume a spherical cow
        }

        ~FEventCameraManager()
        {
            delete _davis;
        }

        void performTask(double currentTime)
        {
            Davis346::location_t vehicleLocation = getLocation(_vehiclePawn);
            Davis346::location_t targetLocation = getLocation(_targetPawn);

			debug("vehicle: %+3.3f %+3.3f %+3.3f    target: %+3.3f %+3.3f %+3.3f",
				vehicleLocation.x, vehicleLocation.y, vehicleLocation.z,
				targetLocation.x, targetLocation.y, targetLocation.z);
        }
}; 
