// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SDPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SPATIALDISPLACEMENT_API ASDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASDPlayerController();

	virtual void SetupInputComponent()override;

protected:
	virtual void BeginPlay() override;
	
private:
	class ASDPawn* SDPawnRef;

	void Up(float AxisValue);
	void Turn(float AxisValue);
};
