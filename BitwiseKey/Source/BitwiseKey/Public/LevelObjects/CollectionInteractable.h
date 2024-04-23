// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BWK_RandomizerBase.h"
#include "CollectionInteractable.generated.h"

/**
 * 
 */
class ABitwiseGameMode;
class ABitwiseGameState;
class UMaterialInterface;
class APlayerController;
class ASpawnPowerup;
class ABWK_RandomizerBase;
class APlayerCharacter;
struct FLinearColor;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BITWISEKEY_API UCollectionInteractable : public UInteractionComponent
{
	GENERATED_BODY()


public:
	UCollectionInteractable();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Interact(APlayerController* playerController) override;

	//UPROPERTY(EditAnywhere, blueprintReadOnly, Category = Interaction)
	//	FString Powerup;
	
protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, blueprintReadWrite, Category = Audio)
		TObjectPtr<class UAudioComponent> CollectionSound;


protected:


	float StartZ;
	TObjectPtr<ABitwiseGameMode> gm;
	TObjectPtr<ABitwiseGameState> gs; 
	
	UPROPERTY(EditAnywhere, blueprintReadWrite)
	TObjectPtr<ABWK_RandomizerBase> Randomizer;



};
