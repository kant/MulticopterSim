/*
* Class implementation for pawn using simulated event camera
*
* Copyright (C) 2018 Simon D. Levy
*
* MIT License
*/

#include "EventCameraPawn.h"
#include "TargetPawn.h"

AEventCameraPawn::AEventCameraPawn()
{
    _phantom.build(this);

    _cameraImage = cv::Mat::zeros(CAMERA_ROWS, CAMERA_COLS, CV_8UC3);

    _eventCameraManager = NULL;
}

void AEventCameraPawn::PostInitializeComponents()
{
    _phantom.PostInitializeComponents();

    Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void AEventCameraPawn::BeginPlay()
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
        _eventCameraManager = new FEventCameraManager(this, (ATargetPawn *)foundActors[0]);
    }

    Super::BeginPlay();
}

void AEventCameraPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    _phantom.EndPlay();
    
    _eventCameraManager = (FEventCameraManager *)FThreadedManager::stopThreadedManager(_eventCameraManager);

    Super::EndPlay(EndPlayReason);
}

// Called automatically on main thread
void AEventCameraPawn::Tick(float DeltaSeconds)
{
    _phantom.Tick();

    cv::imshow("EventCamera", _cameraImage);
    cv::waitKey(1);

    Super::Tick(DeltaSeconds);
}


