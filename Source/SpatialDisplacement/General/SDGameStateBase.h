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

public:
	ASDGameStateBase();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = "Statistics")
		int score = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Statistics")
		float time;

	UPROPERTY(Transient)
		bool bIsRestarting;

	UFUNCTION(Category = "Statistics")
		void AddScore(int32 ScoreToAdd);

	UFUNCTION()
		void RestartLevel();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Transient)
		class ASpatialDisplacementGameModeBase* SDGameMode;
};
