// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CollectionInteractable.h"
#include "XRayVision.generated.h"

/**
 * 
 */

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MILESTONES_API UXRayVision : public UCollectionInteractable
{
	GENERATED_BODY()

public:
	UXRayVision();

	//UPROPERTY(Editanywhere)

	virtual void Interact(APlayerController* playerController) override;
};
