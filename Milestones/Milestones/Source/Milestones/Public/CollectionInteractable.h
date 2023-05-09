// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionComponent.h"
#include "CollectionInteractable.generated.h"

/**
 * 
 */
UCLASS()
class MILESTONES_API UCollectionInteractable : public UInteractionComponent
{
	GENERATED_BODY()

public:
	UCollectionInteractable();

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Interact(APlayerController* playerController) override;


};
