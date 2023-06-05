// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PlayerCharacter.h"
#include "Delegates/Delegate.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "CustomGameMode.generated.h"


/**
 * 
 */

class APlayerCharacter;
class ACustomGameState;
class APawnPowerup;

UCLASS()
class MILESTONES_API ACustomGameMode : public AGameMode
{
	GENERATED_BODY()

public:	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Powerups")
		float invis_precision;

	//sound waves to play when you activate and deactivate invisibility
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Audio)
		USoundWave* SW_InvisActivate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Audio)
		USoundWave* SW_InvisDeactivate;

public:
	ACustomGameMode();
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCollectedXrayDelegate);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCollectedXrayDelegate OnCollectedXray;

	void randomizePowerups();

	void CollectXRay();
	
	void CollectInvisibility();
	void ToggleInvisibility();
	void updateInvisCharge();

	TObjectPtr<ACustomGameState> gs;

	//spawn locations
	//spawned in the xray spot
	UPROPERTY(EditAnywhere, Category = "Collectibles")
		TSubclassOf<AActor> XRayCollectible;
	//spawned in the invisibility spot
	UPROPERTY(EditAnywhere,  Category = "Collectibles")
		TSubclassOf<AActor> InvisibilityCollectible;
	//spawned in the movement ability spot
	UPROPERTY(EditAnywhere, Category = "Collectibles")
		TSubclassOf<AActor> MovementAbilityCollectible;
	//spawned in the teleport ability spot
	UPROPERTY(EditAnywhere, Category = "Collectibles")
		TSubclassOf<AActor> TeleportAbilityCollectible;

	//prefabs to spawn from
	//spawned in the maze
	AActor* MazeCollectible;
	//spawned in the enemy room
	AActor* EnemyCollectible;
	//spawned in the room for whatever movement ability I decide to use
	AActor* MovementRoomCollectible;
	//spawned in the teleport room
	AActor* TeleportCollectible;

	FTimerHandle InvisRechargeTimerHandle;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
		float InvisIncrement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
		float InvisDecrement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
		float InvisMaxCharge;


private:
	TArray<AActor*> PowerupSpawnLocations;
};
