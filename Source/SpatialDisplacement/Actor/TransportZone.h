// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Zone.h"
#include "Enums/CartesianDirectionEnum.h"
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
		ATransportZone* TargetZone;

	UPROPERTY(EditInstanceOnly)
		ECartesianDirection TransportAxis = ECartesianDirection::X;
};
