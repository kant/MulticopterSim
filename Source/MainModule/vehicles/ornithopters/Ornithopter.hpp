/*
 * Vehicle subclass for ornithopters
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include "../MainModule/Vehicle.hpp"

class Ornithopter : public Vehicle {

    public:

        Ornithopter(MultirotorDynamics* dynamics)
            : Vehicle(dynamics)
        {
        }

        virtual ~Ornithopter(void)
        {
        }

        void addWing(UStaticMesh * wingMesh, UStaticMesh * hingeMesh, float hingeX, float hingeY, float wingY, float angle)
        {
            // Use a tiny hinge as the "propeller" for this wing
            UStaticMeshComponent* hingeMeshComponent = Vehicle::makeProp(hingeMesh, hingeX, hingeY, 0);

            // Add the actual wing to the hinge
            UStaticMeshComponent* wingMeshComponent =
                _pawn->CreateDefaultSubobject<UStaticMeshComponent>(makeName("Wing", _propCount, "Mesh"));
            wingMeshComponent->SetStaticMesh(wingMesh);
            wingMeshComponent->SetupAttachment(hingeMeshComponent, USpringArmComponent::SocketName);
            wingMeshComponent->AddRelativeLocation(FVector(0, wingY, -.05) * 100); // m => cm
            wingMeshComponent->SetRelativeRotation(FRotator(0, angle, 0));
  
            _propCount++;
        }

        virtual void setPropRotation(uint8_t index, float angle) override
        {
            // XXX Remove guard once all wings are working
            if (_propellerMeshComponents[index]) {
                _propellerMeshComponents[index]->SetRelativeRotation(FRotator(0, 0, 45*sin(angle/100)));
            }
        }


};  // class Ornithopter