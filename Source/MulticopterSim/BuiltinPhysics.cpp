/*
 * BuiltinPhysics.cpp: Physics class implemenation using UE4 built-in physics
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "BuiltinPhysics.h"

BuiltinPhysics::BuiltinPhysics(void)
{
    _flightManager = FlightManager::createFlightManager();
}

void BuiltinPhysics::start(void)
{
    // Initialize simulation variables
    _eulerXPrev = 0;
    _eulerYPrev = 0;
    _eulerZPrev = 0;
}

TArray<float> BuiltinPhysics::update(float deltaSeconds, AVehiclePawn * vehiclePawn, class UStaticMeshComponent* vehicleMesh)
{
    // Convert quaternion to Euler angles
	FVector euler = FMath::DegreesToRadians(vehiclePawn->GetActorQuat().Euler());

	// Get the simulated IMU readings
	FQuat quat = vehiclePawn->GetActorQuat();
	quat.X = -quat.X;
	quat.Y = -quat.Y;

    // Simulate a gyrometer by temporal first-differencing of Euler angles
    FVector gyro;
    gyro.X = (euler.X - _eulerXPrev) / deltaSeconds;
    gyro.Y = (euler.Y - _eulerYPrev) / deltaSeconds;
    gyro.Z = (euler.Z - _eulerZPrev) / deltaSeconds;

    // Update the flight manager with the quaternion and gyrometer, getting the resulting motor values
    TArray<float> motorvals = _flightManager->update(deltaSeconds, quat, gyro);

    // Store current Euler X,Y for gyro simulation
    _eulerXPrev = euler.X;
    _eulerYPrev = euler.Y;
    _eulerZPrev = euler.Z;

    // Use physics model to compute rotation and translation forces on vehicle
    FVector rotationForce = { 0,0,0 };
    FVector translationForce = { 0,0,0 };
    computeForces(deltaSeconds, motorvals, euler, rotationForce, translationForce);

    // Add movement force vector to vehicle 
    vehicleMesh->AddForce(translationForce);

    // Add rotation to vehicle 
    vehiclePawn->AddActorLocalRotation(deltaSeconds * FRotator(rotationForce.Y, rotationForce.Z, rotationForce.X) * (180 / M_PI));

    // Output the motor values for audiovisual effect
    return motorvals;
}

void BuiltinPhysics::computeForces(float deltaSeconds, TArray<float> motorValues, FVector & euler, FVector & rotationForce, FVector & translationForce)
{
    // Convert motor values to rotational forces
    rotationForce.X = motorsToAngularForce(motorValues, 2, 3, 0, 1);
    rotationForce.Y = motorsToAngularForce(motorValues, 1, 3, 0, 2);
    rotationForce.Z = motorsToAngularForce(motorValues, 1, 2, 0, 3);

    // Rotate Euler angles into inertial frame: http://www.chrobotics.com/library/understanding-euler-angles
    float x = sin(euler.X)*sin(euler.Z) + cos(euler.X)*cos(euler.Z)*sin(euler.Y);
    float y = cos(euler.X)*sin(euler.Y)*sin(euler.Z) - cos(euler.Z)*sin(euler.X);
    float z = cos(euler.Y)*cos(euler.X);

    // Use rotated Euler angles to compute translation force
    translationForce = THRUST_FACTOR * sum(motorValues) * FVector(-x, -y, z);
}

float BuiltinPhysics::motorsToAngularForce(TArray<float> motorValues, uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
    float v = ((motorValues[a] + motorValues[b]) - (motorValues[c] + motorValues[d]));

    return (v < 0 ? -1 : +1) * fabs(v);
}

float BuiltinPhysics::sum(TArray<float> x)
{
    float s = 0.f;

    for (auto it = x.CreateConstIterator(); it; ++it) {
        s += *it;
    }

    return s;
}

/*
FVector BuiltinPhysics::getAccelerometer(float velocityZ, FVector & euler, float deltaSeconds)
{
    // Use velocity first difference to emulate G force on vehicle in inertial frame
    float vario = velocityZ / 100; // m/s
    float gs = ((vario - _varioPrev) / deltaSeconds + AVehiclePawn::G) / AVehiclePawn::G;
    _varioPrev = vario;

    // Convert inertial frame to body frame
    // See slide 50 from https://slideplayer.com/slide/2813564/
    float phi = euler.X;
    float theta = euler.Y;
    return gs * FVector(-sin(theta), sin(phi)*cos(theta), cos(phi)*cos(theta));
}
*/