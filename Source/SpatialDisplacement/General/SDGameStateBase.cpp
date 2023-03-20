// Fill out your copyright notice in the Description page of Project Settings.


#include "SDGameStateBase.h"
#include "Kismet/GameplayStatics.h"

void ASDGameStateBase::BeginPlay()
{
    Super::BeginPlay();

    CurrentLevel = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
    GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("GameState Ready!"));
}