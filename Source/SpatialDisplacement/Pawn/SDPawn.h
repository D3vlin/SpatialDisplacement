// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SDPawn.generated.h"

UCLASS()
class SPATIALDISPLACEMENT_API ASDPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASDPawn();

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float upForce = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float torqueForce = 75.f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float fuel = 8.f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float massInKg = 0.01f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float angularDamping = 100.f;

	UPROPERTY(VisibleDefaultsOnly, Category = "Movement")
		bool canTurn = false;

	UPROPERTY(VisibleDefaultsOnly, Category = "Movement")
		FRotator initialRotation;

	UPROPERTY(EditDefaultsOnly, Category = "WinConditions")
		float landingTime = 5.f;

	UPROPERTY(VisibleDefaultsOnly, Category = "WinConditions")
		bool bIsLanding = false;

	UPROPERTY(VisibleDefaultsOnly, Category = "WinConditions")
		FString currentLevel;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Up(float AxisValue);
	void Turn(float AxisValue);
	void ToLand();
	void PrintState();

};