#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

UENUM(BlueprintType)
enum class ECartesianDirection : uint8
{
	X UMETA(DisplayName = "X"),
	Y UMETA(DisplayName = "Y"),
	Z UMETA(DisplayName = "Z")
};