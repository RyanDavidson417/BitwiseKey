// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BWK_RandomizerBase.h"
#include "BWK_PowerupRandomizer.generated.h"

class UCollectionInteractable;

/**
 * 
 */
UCLASS()
class BITWISEKEY_API ABWK_PowerupRandomizer : public ABWK_RandomizerBase
{
	GENERATED_BODY()

public:
	virtual ~ABWK_PowerupRandomizer() noexcept = default;


	virtual void RandomizeOrder() override;
	virtual void PlaceItems() override;


protected:
	
};
