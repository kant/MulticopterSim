/*
* Class implementation for Phantom pawn in MulticopterSim
*
* Copyright (C) 2018 Simon D. Levy
*
* MIT License
*/

#include "HoverPhantomPawn.h"

AHoverPhantomPawn::AHoverPhantomPawn()
{
    _phantom.build(this);
}

void AHoverPhantomPawn::PostInitializeComponents()
{
    _phantom.PostInitializeComponents();

    Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void AHoverPhantomPawn::BeginPlay()
{
    _phantom.BeginPlay(new FHoverFlightManager(&_phantom.dynamics));

    Super::BeginPlay();
}

void AHoverPhantomPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    _phantom.EndPlay();

    Super::EndPlay(EndPlayReason);
}

// Called automatically on main thread
void AHoverPhantomPawn::Tick(float DeltaSeconds)
{
    _phantom.Tick();

    Super::Tick(DeltaSeconds);
}


