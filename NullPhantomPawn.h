/*
* Class declaration for pawn class using stubbed flight manager
*
* Copyright (C) 2019 Simon D. Levy
*
* MIT License
*/

#pragma once

#include "NullFlightManager.hpp"

#include "../MainModule/Vehicle.hpp"
#include "../MainModule/dynamics/QuadXAP.hpp"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "NullPhantomPawn.generated.h"

UCLASS(Config=Game)
class FLIGHTMODULE_API ANullPhantomPawn : public APawn {

    private:

        GENERATED_BODY()

        MultirotorDynamics::params_t _params = {

            // XXX These parameters are for a much larger vehicle
            5.30216718361085E-05,   // b
            2.23656692806239E-06,   // d
            16.47,                  // m
            0.6,                    // l
            2,                      // Ix
            2,                      // Iy
            3,                      // Iz
            3.08013E-04,            // Jr

            // maxrpm, estimated
            15000,                  

            0                       // XXX motor acceleration }; 
        }; 

        QuadXAPDynamics _dynamics = QuadXAPDynamics(_params);

        Vehicle _vehicle = Vehicle(&_dynamics);

        // Threaded worker for flight control
        FFlightManager * _flightManager = NULL;

        void addProp(uint8_t index, int8_t x, int8_t y, UStaticMesh * mesh);

    protected:

        // AActor overrides

        virtual void BeginPlay() override;

        virtual void Tick(float DeltaSeconds) override;

        virtual void PostInitializeComponents() override;

        virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

        // virtual void NotifyHit(...) override

    public:	

        ANullPhantomPawn();

}; // ANullPhantomPawn
