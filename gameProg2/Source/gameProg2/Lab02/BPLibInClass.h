// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPLibInClass.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROG2_API UBPLibInClass : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	public:
		static FVector MoveTowards(const FVector &startPos, const FVector &endPos, float maxDist);
		
};
