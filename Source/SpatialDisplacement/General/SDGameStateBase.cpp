// Fill out your copyright notice in the Description page of Project Settings.


#include "SDGameStateBase.h"

void ASDGameStateBase::BeginPlay()
{
    Super::BeginPlay();

    GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("GameState Ready!"));
}