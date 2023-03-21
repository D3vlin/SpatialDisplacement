// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stage.generated.h"

UCLASS()
class SPATIALDISPLACEMENT_API AStage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStage();

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		class UBoxComponent* BoxCollision;

	UPROPERTY(EditInstanceOnly, Category = "WinConditions")
		bool bInitialStage = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
