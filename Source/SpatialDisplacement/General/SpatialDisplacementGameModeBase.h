// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpatialDisplacementGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SPATIALDISPLACEMENT_API ASpatialDisplacementGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleDefaultsOnly)
		FString currentLevel;

	UPROPERTY(Transient)
		TObjectPtr<class ASDCameraActor> CameraActor;

	UPROPERTY(EditDefaultsOnly, Category = "WinConditions")
		float landingTime = 5.f;
};
