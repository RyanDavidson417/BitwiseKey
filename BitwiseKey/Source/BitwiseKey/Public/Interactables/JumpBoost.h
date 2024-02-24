// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/PowerupCollectibleBase.h"
#include "JumpBoost.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = "PowerupComponents", meta = (BlueprintSpawnableComponent))
class BITWISEKEY_API UJumpBoost : public UPowerupCollectibleBase
{
	GENERATED_BODY()
	


public:
	void CollectPowerup(APlayerController* playerController) override;
	void Reset() override;
};
