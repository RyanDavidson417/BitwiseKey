// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerupDataBase.h"
#include "CollectionInteractable.h"
#include "BitwiseGameState.h"
#include "BitwiseKey//BitwiseKey.h"
#include "PowerupCollectibleBase.generated.h"

/**
 * 
 */

class ASpawnPowerup;
class UPowerupDataBase;
UCLASS()
class BITWISEKEY_API UPowerupCollectibleBase : public UCollectionInteractable
{
	GENERATED_BODY()



public:


	virtual void CollectPowerup(APlayerController* playerController);

	void Interact(APlayerController* playerController) override;
	UFUNCTION()
	virtual void Reset();
	virtual void BeginPlay() override;

protected:
	APlayerController* MPlayerController;
};
