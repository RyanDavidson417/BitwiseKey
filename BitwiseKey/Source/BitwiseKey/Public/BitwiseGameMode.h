// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BitwiseGameState.h"
#include "PlayerCharacter.h"
#include "Delegates/Delegate.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "BitwiseGameMode.generated.h"


/**
 * 
 */

class APlayerCharacter;
class AGameState;
class APawnPowerup;
class UXRayVision;
class UInvisibilityPowerup;
class UCollectionInteractable;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResetDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCollectedXrayDelegate);

USTRUCT(BlueprintType)
struct FPlayerStatStruct {
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName name;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
	float currentCharge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
	float ChargeRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
	float DischargeRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
	float MaxCharge;
	//how many "units" the progress bar has
	UPROPERTY(EditAnywhere, Category = "Powerups")
	float Precision;
	
	FTimerHandle RechargeTimerHandle;



};

UCLASS()
class BITWISEKEY_API ABitwiseGameMode : public AGameMode
{
	GENERATED_BODY()

		//functions
public:	
	ABitwiseGameMode();

	void CollectXRay();

	void CollectInvisibility();
	void ToggleInvisibility();
	void ToggleStamina();
	void UpdateInvisCharge();
	void UpdateStamina();

	void StartGameTimer();

	UFUNCTION(BlueprintCallable)
	void ResetGameMode();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:


		//variables
public:
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FOnResetDelegate D_OnReset;	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCollectedXrayDelegate OnCollectedXray;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float BitwiseGameTimer = 0;

		//the number of individual 'units' within each progress bar


	//sound waves to play when you activate and deactivate invisibility
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Audio)
		USoundWave* SW_InvisActivate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Audio)
		USoundWave* SW_InvisDeactivate;

	TObjectPtr<ABitwiseGameState> gs;
	TObjectPtr<APlayerCharacter> playerCharacter;

	//prefabs to spawn from
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

	//spawn locations
	//spawned in the maze
	AActor* MazeCollectible;
	//spawned in the enemy room
	AActor* EnemyCollectible;
	//spawned in the room for whatever movement ability I decide to use
	AActor* MovementRoomCollectible;
	//spawned in the teleport room
	AActor* TeleportCollectible;

	AActor* LastSpawnedPowerup;
	
	FPlayerStatStruct InvisibilityStruct;
	FPlayerStatStruct StaminaStruct;


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
		float StaminaChargeRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
		float StaminaDischargeRate;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
		float StaminaMaxCharge;


	TArray<AActor*> SpawnedCollectibles;


private:
	float GameStartTime;

	TArray<AActor*> PowerupSpawnLocations;
};
