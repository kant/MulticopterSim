/*
* Class implementation for Phantom pawn in MulticopterSim
*
* Copyright (C) 2018 Simon D. Levy
*
* MIT License
*/

#include "NullPhantomPawn.h"

// Structures to hold static mesh initializations
DECLARE_STATIC_MESH(FFrameStatics, "Phantom/Frame.Frame", FrameStatics)
DECLARE_STATIC_MESH(FProp1Statics, "Phantom/Prop.Prop", Prop1Statics)
DECLARE_STATIC_MESH(FProp2Statics, "Phantom/Prop.Prop", Prop2Statics)
DECLARE_STATIC_MESH(FProp3Statics, "Phantom/Prop.Prop", Prop3Statics)
DECLARE_STATIC_MESH(FProp4Statics, "Phantom/Prop.Prop", Prop4Statics)

ANullPhantomPawn::ANullPhantomPawn()
{
    _vehicle.build(this, FrameStatics.mesh.Get());

    // Add propellers
    addProp(1, +1, +1, Prop1Statics.mesh.Get());
    addProp(2, -1, -1, Prop2Statics.mesh.Get());
    addProp(3, +1, -1, Prop3Statics.mesh.Get());
    addProp(4, -1, +1, Prop4Statics.mesh.Get());
}

void ANullPhantomPawn::PostInitializeComponents()
{
    _vehicle.PostInitializeComponents();

    Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void ANullPhantomPawn::BeginPlay()
{
    _flightManager = new FNullFlightManager(&_dynamics);

    _vehicle.BeginPlay(_flightManager);

    Super::BeginPlay();
}

void ANullPhantomPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    _flightManager = (FNullFlightManager *)FThreadedWorker::stopThreadedWorker(_flightManager);

    Super::EndPlay(EndPlayReason);
}

// Called automatically on main thread
void ANullPhantomPawn::Tick(float DeltaSeconds)
{
    _vehicle.Tick();

    Super::Tick(DeltaSeconds);
}

void ANullPhantomPawn::addProp(uint8_t index, int8_t x, int8_t y, UStaticMesh * mesh)
{
    float d = 0.12;

    _vehicle.addProp(index-1, x*d, y*d, +.15, mesh);
}


