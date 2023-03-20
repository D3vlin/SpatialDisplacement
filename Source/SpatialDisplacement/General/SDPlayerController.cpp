// Fill out your copyright notice in the Description page of Project Settings.


#include "SDPlayerController.h"
#include "Pawn/SDPawn.h"

ASDPlayerController::ASDPlayerController()
{

}

void ASDPlayerController::BeginPlay()
{
    Super::BeginPlay();

    PawnActor = Cast<ASDPawn>(GetPawn());

    SetupInputComponent();

    GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("PlayerController Ready!"));
}

void ASDPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (PawnActor)
    {
        InputComponent->BindAxis("Up", this, &ASDPlayerController::Up);
        InputComponent->BindAxis("Turn", this, &ASDPlayerController::Turn);
    }
}

void ASDPlayerController::Up(float AxisValue)
{
    if (PawnActor) {
        PawnActor->Up(AxisValue);
    }
}

void ASDPlayerController::Turn(float AxisValue)
{
    if (PawnActor)
        PawnActor->Turn(AxisValue);
}