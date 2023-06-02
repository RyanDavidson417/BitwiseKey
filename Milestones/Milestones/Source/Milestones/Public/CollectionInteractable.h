// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionComponent.h"
#include "CollectionInteractable.generated.h"

/**
 * 
 */
class ACustomGameMode;
class ACustomGameState;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MILESTONES_API UCollectionInteractable : public UInteractionComponent
{
	GENERATED_BODY()


public:
	UCollectionInteractable();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Interact(APlayerController* playerController) override;

	//UPROPERTY(EditAnywhere, blueprintReadOnly, Category = Interaction)
	//	FString Powerup;
public:

	UPROPERTY(EditAnywhere, blueprintReadWrite, Category = Audio)
		TObjectPtr<class UAudioComponent> CollectionSound;

protected:
	virtual void BeginPlay() override;

	TObjectPtr<ACustomGameMode> gm;
	TObjectPtr<ACustomGameState> gs; 

	float StartZ;
};
