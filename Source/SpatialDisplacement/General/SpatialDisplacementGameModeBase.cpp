// Copyright Epic Games, Inc. All Rights Reserved.


#include "SpatialDisplacementGameModeBase.h"
#include "Camera/SDCameraActor.h"
#include "Kismet/GameplayStatics.h"

void ASpatialDisplacementGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    currentLevel = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);

    CameraActor = Cast<ASDCameraActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ASDCameraActor::StaticClass()));

    if (CameraActor)
        GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(CameraActor);

    GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("GameMode Ready!"));
}