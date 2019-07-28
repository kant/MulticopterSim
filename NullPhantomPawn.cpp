/*
* Class implementation for Phantom pawn with stubbed flight manager
*
* Copyright (C) 2018 Simon D. Levy
*
* MIT License
*/

#include "../MainModule/pawns/Phantom.hpp"

#include "NullFlightManager.hpp"

class ANullPhantomPawn : public APhantomPawn {


    ANullPhantomPawn() : APhantomPawn()
    {
    }

    void PostInitializeComponents() 
    {
        APhantomPawn::PostInitializeComponents();
    }

    // Called when the game starts or when spawned
    void BeginPlay()
    {
        APhantomPawn::BeginPlay(new FNullFlightManager(&_dynamics));
    }

    void EndPlay(const EEndPlayReason::Type EndPlayReason)
    {
        APhantomPawn::EndPlay(EndPlayReason);
    }

    // Called automatically on main thread
    void Tick(float DeltaSeconds)
    {
        APhantomPawn::Tick(DeltaSeconds);
    }

}; // class ANullPhantomPawn
