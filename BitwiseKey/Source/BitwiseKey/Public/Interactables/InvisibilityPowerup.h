// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerupCollectibleBase.h"
#include "InvisibilityPowerup.generated.h"

/**
 * 
 */

UCLASS(ClassGroup = "PowerupComponents", meta = (BlueprintSpawnableComponent))
class BITWISEKEY_API UInvisibilityPowerup : public UPowerupCollectibleBase
{
	GENERATED_BODY()

public:
	UInvisibilityPowerup();

	virtual void Interact(APlayerController* playerController) override;
	void CollectPowerup(APlayerController* playerController) override;
};
