// Fill out your copyright notice in the Description page of Project Settings.


#include "SDPlayerController.h"
#include "SDPawn.h"

ASDPlayerController::ASDPlayerController()
{

}

void ASDPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SDPawnRef = Cast<ASDPawn>(GetPawn());

    SetupInputComponent();
}

void ASDPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (SDPawnRef)
    {
        InputComponent->BindAxis("Up", this, &ASDPlayerController::Up);

        InputComponent->BindAxis("Turn", this, &ASDPlayerController::Turn);
    }
}

void ASDPlayerController::Up(float AxisValue)
{
    if (SDPawnRef)
        SDPawnRef->Up(AxisValue);
}

void ASDPlayerController::Turn(float AxisValue)
{
    if (SDPawnRef)
        SDPawnRef->Turn(AxisValue);
}