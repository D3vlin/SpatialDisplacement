// Fill out your copyright notice in the Description page of Project Settings.


#include "SDPawn.h"
#include "Kismet/GamePlayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "SpatialDisplacement/General/SpatialDisplacementGameModeBase.h"
#include "SpatialDisplacement/Actor/Stage.h"
#include "SpatialDisplacement/Actor/TransportZone.h"

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
	StaticMesh->SetGenerateOverlapEvents(true);
	RootComponent = StaticMesh;

	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ASDPawn::OnOverlapBegin);
	StaticMesh->OnComponentEndOverlap.AddDynamic(this, &ASDPawn::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ASDPawn::BeginPlay()
{
	Super::BeginPlay();

	currentWorld = GetWorld();
	SDGameMode = (ASpatialDisplacementGameModeBase*) currentWorld->GetAuthGameMode();
	currentLevel = UGameplayStatics::GetCurrentLevelName(currentWorld, false);
	initialRotation = GetActorRotation();
	landingTime = SDGameMode->landingTime;
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
		SDGameMode->RestartLevel();
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
	if (currentRotation != initialRotation && landingTime > 0)
	{
		FRotator targetRotation = UKismetMathLibrary::RInterpTo(currentRotation, initialRotation, DeltaTime, 7.0f);
		SetActorRotation(targetRotation);
	}

	if (landingTime <= 0)
		SDGameMode->RestartLevel();
}

void ASDPawn::PrintState() {
	GEngine->AddOnScreenDebugMessage(-1, .0f, FColor::Yellow, FString::Printf(TEXT("Ubicacion = %s"), *GetActorLocation().ToString()));
	//GEngine->AddOnScreenDebugMessage(-1, .0f, FColor::Yellow, FString::Printf(TEXT("R Inicial = %s, R Actual = %s"), *initialRotation.ToString(), *GetActorRotation().ToString()));
	//GEngine->AddOnScreenDebugMessage(-1, .0f, FColor::Yellow, FString::Printf(TEXT("Puede rotar = %d"), (bCanTurn) ? 1 : 0));
	GEngine->AddOnScreenDebugMessage(-1, .0f, FColor::Yellow, FString::Printf(TEXT("Fuel = %f"), fuel));
	GEngine->AddOnScreenDebugMessage(-1, .0f, FColor::Yellow, FString::Printf(TEXT("Velocidad = %s"), *StaticMesh->GetComponentVelocity().ToString()));

	if (landingTime <= 0)
		GEngine->AddOnScreenDebugMessage(-1, .0f, FColor::Green, FString::Printf(TEXT("Aterrizaste")));
	else
		GEngine->AddOnScreenDebugMessage(-1, .0f, FColor::Orange, FString::Printf(TEXT("Aterrizando = %d, TAterrizaje = %f"), (bIsLanding) ? 1 : 0, landingTime));
}

void ASDPawn::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AStage::StaticClass()))
	{
		AStage* stage = Cast<AStage>(OtherActor);

		bCanTurn = false;
		if (!stage->bInitialStage)
		{
			bIsLanding = true;
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, FString::Printf(TEXT("Inicio aterrizaje")));
		}
	}
	else if (OtherActor->IsA(ATransportZone::StaticClass()))
	{
		currentTransport = Cast<ATransportZone>(OtherActor);
		if (currentTransport->TargetZone && !bIsTransported)
		{
			FVector currentLocation = GetActorLocation();
			FVector targetLocation = currentTransport->TargetZone->GetActorLocation();

			if (currentTransport->TransportAxis == ECartesianDirection::Z)
				targetLocation.Y = currentLocation.Y;
			else if (currentTransport->TransportAxis == ECartesianDirection::Y)
				targetLocation.Z = currentLocation.Z;

			bIsTransported = true;
			SetActorLocation(targetLocation);
		}
	}
}

void ASDPawn::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AStage::StaticClass()))
	{
		bIsLanding = false;
		landingTime = SDGameMode->landingTime;
		bCanTurn = !bIsLanding;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, FString::Printf(TEXT("Plataforma abandonada")));
	}
	else if (OtherActor->IsA(ATransportZone::StaticClass()))
	{
		if (currentTransport != Cast<ATransportZone>(OtherActor))
		{
			bIsTransported = false;
			currentTransport = nullptr;
		}
	}
}