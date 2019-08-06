/*
* Class implementation for Phantom pawn in MulticopterSim
*
* Copyright (C) 2018 Simon D. Levy
*
* MIT License
*/

#include "HoverPhantomPawn.h"
#include "TargetPawn.h"

AHoverPhantomPawn::AHoverPhantomPawn()
{
    _phantom.build(this);

    _targetPawn = NULL;
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

    // Get all target actors in scene 
    TArray<AActor*> foundActors;
    UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), ATargetPawn::StaticClass(), foundActors);

    // Use the first one found
    if (foundActors.Num() == 0) {
        debug("No TargetPawn object found in scene");
    }
    else {
        _targetPawn = (ATargetPawn *)foundActors[0];
    }

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

    debug("%p", _targetPawn);

    Super::Tick(DeltaSeconds);
}


