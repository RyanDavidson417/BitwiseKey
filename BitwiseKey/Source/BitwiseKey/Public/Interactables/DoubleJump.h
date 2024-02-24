// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/PowerupCollectibleBase.h"
#include "DoubleJump.generated.h"

/**
 * 
 */
UCLASS()
class BITWISEKEY_API UDoubleJump : public UPowerupCollectibleBase
{
	GENERATED_BODY()
	

public:
	void CollectPowerup(APlayerController* playerController) override;
	void Reset() override;
};
