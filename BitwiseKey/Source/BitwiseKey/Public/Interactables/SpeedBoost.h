// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/PowerupCollectibleBase.h"
#include "SpeedBoost.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = "PowerupComponents", meta = (BlueprintSpawnableComponent))
class BITWISEKEY_API USpeedBoost : public UPowerupCollectibleBase
{
	GENERATED_BODY()

public: 
	void CollectPowerup(APlayerController* playerController) override;
};
