// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SDGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class SPATIALDISPLACEMENT_API ASDGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(VisibleDefaultsOnly, Category = "WinConditions")
		float landingTime;

	UPROPERTY(VisibleDefaultsOnly)
		FString currentLevel;

	UFUNCTION()
		void RestartLevel();

	UFUNCTION()
		void OpenLevel();

private:
	UPROPERTY(Transient)
		class ASpatialDisplacementGameModeBase* SDGameMode;
};
