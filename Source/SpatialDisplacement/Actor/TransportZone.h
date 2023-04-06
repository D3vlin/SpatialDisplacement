// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Zone.h"
#include "TransportZone.generated.h"

/**
 * 
 */
UCLASS()
class SPATIALDISPLACEMENT_API ATransportZone : public AZone
{
	GENERATED_BODY()

public:
	ATransportZone();

	UPROPERTY(EditInstanceOnly)
		USceneComponent* TargetPosition;

	UPROPERTY(EditInstanceOnly)
		ATransportZone* TargetZone;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	
};
