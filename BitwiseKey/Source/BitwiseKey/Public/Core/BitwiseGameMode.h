// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BitwiseGameState.h"
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCollectedAbilitySignature, EPowerUpName, PowerUpName);


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

	//concept: rather than separate functions for each ability, could we do one Collect(EPowerup powerUp)
	// then iterate over the list of powerups until we find a match. I don't want to experiment with this now
	// since I've already spent a long time on this refactor. I'm also wary of whether it'd properly update
	// the references (since the TMap doesn't store them as pointers). so we may need to refactor it to a TArray.
	// but this could be worth keeping in mind. much cleaner function call at the expense of a very small loop
	//



	void CollectXRay();
	void CollectInvisibility();
	void CollectSpeedBoost();
	void CollectJumpBoost();
	//
	//void CollectPowerup(UPowerupDataBase* powerup);
	
	void ToggleInvisibility();


	void UpdateInvisCharge();
	void UpdateStamina();

	void StartGameTimer();

	UFUNCTION(BlueprintCallable)
	void ResetGameMode();


	UFUNCTION(BlueprintImplementableEvent)
	void WinGame();//no C++ implementation

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
	FOnCollectedXrayDelegate OnCollectedXray; // this delegate is separate from the generic OnAbilityCollected
	//delegate as xray objects have specific functionality that was implemented prior to the creation
	// of these delegates.After I further research the performance of delegates I may consider refactoring
	// that old functionality to be tied to the new delegate, but for now it stays.  


	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCollectedAbilitySignature OnCollectedAbilityDelegate;




		//the number of individual 'units' within each progress bar


	//sound waves to play when you activate and deactivate invisibility
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Audio)
		USoundWave* SW_InvisActivate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Audio)
		USoundWave* SW_InvisDeactivate;

	TObjectPtr<ABitwiseGameState> gs;
	TObjectPtr<APlayerCharacter> PlayerCharacter;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
	FPlayerStatStruct InvisibilityStatStruct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
	FPlayerStatStruct StaminaStatStruct;

	//used to track whether the gameplay timer should still be running, without pausing everything else
	//useful for game end screens (especially lose screen which uses an animation reliant on tick)
	UPROPERTY(BlueprintReadWrite)
	bool bGameTimerRunning;
	

protected:

	TArray<AActor*> SpawnedCollectibles;


private:
	float GameStartTime;

	TArray<AActor*> PowerupSpawnLocations;
};
