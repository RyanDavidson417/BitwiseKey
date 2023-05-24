// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CollectionInteractable.h"
#include "XRayVision.generated.h"

/**
 * 
 */

class ACustomGameMode;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MILESTONES_API UXRayVision : public UCollectionInteractable
{
	GENERATED_BODY()

public:
	UXRayVision();

	UPROPERTY(Editanywhere);
	//TObjectPtr<class ACustomGameMode> gm;
	TObjectPtr<ACustomGameMode> gm;

	//UPROPERTY(EditAnywhere, blueprintReadOnly, Category = Interaction)
	//	FString Powerup;


protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Interact(APlayerController* playerController) override;
};
