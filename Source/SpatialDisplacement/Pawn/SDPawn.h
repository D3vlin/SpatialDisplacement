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
		float fuel = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float massInKg = 0.01f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float angularDamping = 100.f;

	UPROPERTY(VisibleDefaultsOnly, Category = "Movement")
		bool bCanTurn = false;

	UPROPERTY(VisibleDefaultsOnly, Category = "Movement")
		FRotator initialRotation;

	UPROPERTY(EditDefaultsOnly, Category = "WinConditions")
		float landingTime = 5.f;

	UPROPERTY(VisibleDefaultsOnly, Category = "WinConditions")
		bool bIsLanding = false;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "WinConditions")
		bool bEmptyFuel = false;

	UPROPERTY(VisibleDefaultsOnly, Category = "WinConditions")
		FString currentLevel;

	UPROPERTY(Transient)
		class ASpatialDisplacementGameModeBase* SDGameMode;

	UPROPERTY(Transient)
		UWorld* currentWorld;

	UPROPERTY(Transient)
		bool bIsTransported;

	UPROPERTY(Transient)
		class ATransportZone* currentTransport;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Up(float AxisValue);

	void Turn(float AxisValue);

private:
	void ToLand(float DeltaTime);

	void PrintState();

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
