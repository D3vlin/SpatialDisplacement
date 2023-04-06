// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Zone.h"
#include "Components/BoxComponent.h"

// Sets default values
AZone::AZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("Box Collision"));
	RootComponent = BoxCollision;
}

// Called when the game starts or when spawned
void AZone::BeginPlay()
{
	Super::BeginPlay();
	
}
