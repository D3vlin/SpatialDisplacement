// Fill out your copyright notice in the Description page of Project Settings.


#include "SDPawn.h"
#include "Kismet/GamePlayStatics.h"

// Sets default values
ASDPawn::ASDPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetSimulatePhysics(true);
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
	
	currentLevel = UGameplayStatics::GetCurrentLevelName(GetWorld(), false);
	initialRotation = GetActorRotation();
}

// Called every frame
void ASDPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASDPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASDPawn::Up(float AxisValue) {

}

void ASDPawn::Turn(float AxisValue) {

}

void ASDPawn::ToLand() {

}

void ASDPawn::PrintState() {

}

