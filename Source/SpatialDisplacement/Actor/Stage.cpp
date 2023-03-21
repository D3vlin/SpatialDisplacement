// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Stage.h"
#include "Components/BoxComponent.h"

// Sets default values
AStage::AStage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("Box Collision"));
	BoxCollision->SetupAttachment(StaticMesh);
}

// Called when the game starts or when spawned
void AStage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

