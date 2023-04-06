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

private:
	UPROPERTY(Transient)
		class ASpatialDisplacementGameModeBase* SDGameMode;
};
