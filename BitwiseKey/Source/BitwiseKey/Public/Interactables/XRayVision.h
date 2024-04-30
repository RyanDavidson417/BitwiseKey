// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/PowerupCollectibleBase.h"
#include "XRayVision.generated.h"

/**
 * 
 */

UCLASS(ClassGroup = "PowerupComponents", meta = (BlueprintSpawnableComponent))
class BITWISEKEY_API UXRayVision : public UPowerupCollectibleBase
{
	GENERATED_BODY()

public:
	UXRayVision();

	//UPROPERTY(Editanywhere)

	virtual void Interact_Implementation(APlayerController* playerController) override;
	void CollectPowerup(APlayerController* playerController) override;
};
