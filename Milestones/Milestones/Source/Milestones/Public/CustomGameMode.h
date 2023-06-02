// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PlayerCharacter.h"
#include "CustomGameMode.generated.h"

/**
 * 
 */
class APawnPowerup;

class APlayerCharacter;
class ACustomGameState;
class ABitwisePlayerState;
class ABitwisePlayerController;

UCLASS()
class MILESTONES_API ACustomGameMode : public AGameMode
{
	GENERATED_BODY()

public:	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:
	ACustomGameMode();
	
	void randomizePowerups();

	void CollectXRay();
	void CollectInvisibility();
	

	void ToggleInvisibility();

	TObjectPtr<ACustomGameState> gs;    
	//TObjectPtr<ACustomGameState> gs;    
	TObjectPtr<ABitwisePlayerController> pc;
	TObjectPtr<ABitwisePlayerState> ps;

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


	//spawned in the maze
	AActor* MazeCollectible;
	//spawned in the enemy room
	AActor* EnemyCollectible;
	//spawned in the room for whatever movement ability I decide to use
	AActor* MovementRoomCollectible;
	//spawned in the teleport room
	AActor* TeleportCollectible;


private:
	TArray<AActor*> PowerupSpawnLocations;
};
