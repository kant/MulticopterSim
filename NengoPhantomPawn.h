/*
* Class declaration for pawn class using Nengo flight manager
*
* Copyright (C) 2019 Simon D. Levy
*
* MIT License
*/

#pragma once

#include "../MainModule/vehicles/Phantom.h"

#include "NengoFlightManager.hpp"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "NengoPhantomPawn.generated.h"

UCLASS(Config=Game)
class FLIGHTMODULE_API ANengoPhantomPawn : public APawn {

    private:

        GENERATED_BODY()

        // Helper class
        Phantom _phantom;

    protected:

        // AActor overrides

        virtual void BeginPlay() override;

        virtual void Tick(float DeltaSeconds) override;

        virtual void PostInitializeComponents() override;

        virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

        // virtual void NotifyHit(...) override

    public:	

        ANengoPhantomPawn();

}; // ANengoPhantomPawn
