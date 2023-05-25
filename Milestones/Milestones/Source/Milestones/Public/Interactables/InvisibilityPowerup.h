// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollectionInteractable.h"
#include "InvisibilityPowerup.generated.h"

/**
 * 
 */

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class MILESTONES_API UInvisibilityPowerup : public UCollectionInteractable
{
	GENERATED_BODY()

public:
	UInvisibilityPowerup();

	virtual void Interact(APlayerController* playerController) override;
	
};
