/*
* Class implementation for Phantom pawn in MulticopterSim
*
* Copyright (C) 2018 Simon D. Levy
*
* MIT License
*/

#include "NengoPhantomPawn.h"

ANengoPhantomPawn::ANengoPhantomPawn()
{
    _phantom.build(this);
}

void ANengoPhantomPawn::PostInitializeComponents()
{
    _phantom.PostInitializeComponents();

    Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void ANengoPhantomPawn::BeginPlay()
{
    _phantom.BeginPlay(new FNengoFlightManager(&_phantom.dynamics));

    Super::BeginPlay();
}

void ANengoPhantomPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    _phantom.EndPlay();

    Super::EndPlay(EndPlayReason);
}

// Called automatically on main thread
void ANengoPhantomPawn::Tick(float DeltaSeconds)
{
    _phantom.Tick();

    Super::Tick(DeltaSeconds);
}


