// Fill out your copyright notice in the Description page of Project Settings.


#include "SDPawn.h"
#include "Kismet/GamePlayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASDPawn::ASDPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->BodyInstance.SetMassOverride(massInKg, true);
	StaticMesh->BodyInstance.MassScale = massInKg;
	StaticMesh->BodyInstance.AngularDamping = angularDamping;
	StaticMesh->SetEnableGravity(true);
	StaticMesh->BodyInstance.bLockXTranslation = true;
	StaticMesh->BodyInstance.bLockYRotation = true;
	RootComponent = StaticMesh;
}

// Called when the game starts or when spawned
void ASDPawn::BeginPlay()
{
	Super::BeginPlay();
	
	currentWorld = GetWorld();
	currentLevel = UGameplayStatics::GetCurrentLevelName(currentWorld, false);
	initialRotation = GetActorRotation();
}

// Called every frame
void ASDPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsLanding) {
		ToLand(DeltaTime);
	}

	PrintState();
}

// Called to bind functionality to input
void ASDPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASDPawn::Up(float AxisValue) {
	if (AxisValue > 0 && fuel > 0)
	{
		bEmptyFuel = false;
		float worldDeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(currentWorld);
		fuel -= worldDeltaSeconds;

		FVector force = StaticMesh->GetUpVector() * AxisValue * upForce * worldDeltaSeconds;
		StaticMesh->AddForce(force, NAME_None, false);
		GEngine->AddOnScreenDebugMessage(-1, .0f, FColor::Yellow, FString::Printf(TEXT("ForceVector = %s"), *force.ToString()));
	}
	else if (fuel <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, .0f, FColor::Red, TEXT("Empty!"));
		bEmptyFuel = true;
	}
}

void ASDPawn::Turn(float AxisValue) {
	if (bCanTurn) {
		FRotator rotator = UKismetMathLibrary::MakeRotator((AxisValue * torqueForce * UGameplayStatics::GetWorldDeltaSeconds(currentWorld)), .0f, .0f);
		StaticMesh->AddLocalRotation(rotator);
	}
}

void ASDPawn::ToLand(float DeltaTime) {
	landingTime -= DeltaTime;
	FRotator currentRotation = GetActorRotation();
	if (currentRotation != initialRotation)
	{
		FRotator targetRotation = UKismetMathLibrary::RInterpTo(currentRotation, initialRotation, DeltaTime, 7.0f);
		SetActorRotation(targetRotation);
	}
}

void ASDPawn::PrintState() {
	GEngine->AddOnScreenDebugMessage(-1, .0f, FColor::Yellow, FString::Printf(TEXT("Ubicacion = %s"), *GetActorLocation().ToString()));
	GEngine->AddOnScreenDebugMessage(-1, .0f, FColor::Yellow, FString::Printf(TEXT("R Inicial = %s, R Actual = %s"), *initialRotation.ToString(), *GetActorRotation().ToString()));
	GEngine->AddOnScreenDebugMessage(-1, .0f, FColor::Yellow, FString::Printf(TEXT("Puede rotar = %b"), bCanTurn));
	GEngine->AddOnScreenDebugMessage(-1, .0f, FColor::Yellow, FString::Printf(TEXT("Fuel = %f"), fuel));
	GEngine->AddOnScreenDebugMessage(-1, .0f, FColor::Yellow, FString::Printf(TEXT("Velocidad = %s"), *StaticMesh->GetComponentVelocity().ToString()));

	if (landingTime <= 0)
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Aterrizaste"), bIsLanding, landingTime));
	else
		GEngine->AddOnScreenDebugMessage(-1, .0f, FColor::Yellow, FString::Printf(TEXT("Aterrizando = %b, TAterrizaje = %f"), bIsLanding, landingTime));
}

