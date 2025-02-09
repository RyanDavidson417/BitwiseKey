// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelObjects/PowerupDataBase.h"
#include "LevelObjects/CollectionInteractable.h"
#include "Core/BitwiseGameState.h"
#include "BitwiseKey//BitwiseKey.h"
#include "PowerupCollectibleBase.generated.h"

/**
 * 
 */

class ASpawnPowerup;
class UPowerupDataBase;
struct FTimerHandle;

UCLASS()
class BITWISEKEY_API UPowerupCollectibleBase : public UCollectionInteractable
{
	GENERATED_BODY()



public:


	virtual void CollectPowerup(APlayerController* playerController);

	void Interact_Implementation(APlayerController* playerController) override;
	UFUNCTION()
	virtual void Reset();
	virtual void BeginPlay() override;




	UPROPERTY(EditAnywhere, blueprintReadWrite)
	ASpawnPowerup* SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundBase> TrillSound;

protected:
	APlayerController* MPlayerController;




	UPROPERTY(EditAnywhere, blueprintReadWrite)
	FLinearColor PowerupColor;
	
	UPROPERTY(EditAnywhere, blueprintReadWrite)
	UMaterialInterface* Material;

	UPROPERTY(EditAnywhere, blueprintReadWrite)
	UStaticMeshComponent* PodMesh;
};
