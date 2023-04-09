// Fill out your copyright notice in the Description page of Project Settings.


#include "SDGameStateBase.h"
#include "SpatialDisplacement/General/SpatialDisplacementGameModeBase.h"

ASDGameStateBase::ASDGameStateBase()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASDGameStateBase::BeginPlay()
{
    Super::BeginPlay();

    SDGameMode = (ASpatialDisplacementGameModeBase*)GetWorld()->GetAuthGameMode();
    time = SDGameMode->time;
}

void ASDGameStateBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    time = FMath::Max(.0f, time - DeltaTime);
    if (time <= 0)
        RestartLevel();
}

void ASDGameStateBase::AddScore(int32 ScoreToAdd)
{
    score += ScoreToAdd;
}

void ASDGameStateBase::RestartLevel()
{
    bIsRestarting = true;
    SDGameMode->RestartLevel();
}