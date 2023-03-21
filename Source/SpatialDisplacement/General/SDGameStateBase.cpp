// Fill out your copyright notice in the Description page of Project Settings.


#include "SDGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "SpatialDisplacement/General/SpatialDisplacementGameModeBase.h"

void ASDGameStateBase::BeginPlay()
{
    Super::BeginPlay();

    SDGameMode = (ASpatialDisplacementGameModeBase*) GetWorld()->GetAuthGameMode();

    currentLevel = SDGameMode->currentLevel;
    landingTime = SDGameMode->landingTime;
    GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("GameState Ready!"));
}

void ASDGameStateBase::RestartLevel()
{
    GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Reiniciando!"));
    FTimerHandle Timer;
    GetWorldTimerManager().SetTimer(Timer, this, &ASDGameStateBase::OpenLevel, 3.0f, false);
}

void ASDGameStateBase::OpenLevel()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName(currentLevel));
}