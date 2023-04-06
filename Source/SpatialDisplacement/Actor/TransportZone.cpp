// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/TransportZone.h"

// Sets default values
ATransportZone::ATransportZone() : AZone()
{
	TargetPosition = CreateDefaultSubobject<USceneComponent>(TEXT("TargetPosition"));
	TargetPosition->SetupAttachment(RootComponent);
	TargetPosition->SetRelativeLocation(GetActorLocation());
}

#if WITH_EDITOR
void ATransportZone::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = PropertyChangedEvent.GetPropertyName();

	if (PropertyName == GET_MEMBER_NAME_CHECKED(USceneComponent, RelativeLocation) && TargetPosition)
		TargetPosition->SetRelativeLocation(PropertyChangedEvent.GetPropertyValue()->GetVec3Value());
}
#endif
