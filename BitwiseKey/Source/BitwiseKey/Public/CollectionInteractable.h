// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CollectionInteractable.generated.h"

/**
 * 
 */
class ACustomGameMode;
class ACustomGameState;
class UMaterialInterface;
class ASpawnPowerup;
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

	UPROPERTY(EditAnywhere, blueprintReadWrite)
		ASpawnPowerup* SpawnPoint;

protected:
	

	float StartZ;
	TObjectPtr<ACustomGameMode> gm;
	TObjectPtr<ACustomGameState> gs; 

	UPROPERTY(EditAnywhere, blueprintReadWrite)
		UMaterialInterface* Material;

	UPROPERTY(EditAnywhere, blueprintReadWrite)
		FLinearColor PowerupColor;

	UPROPERTY(EditAnywhere, blueprintReadWrite)
		UStaticMeshComponent* PodMesh;


};
