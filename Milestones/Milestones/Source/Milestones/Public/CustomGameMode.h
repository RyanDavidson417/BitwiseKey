// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PlayerCharacter.h"
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



public:
	ACustomGameMode();
	
	void randomizePowerups();

	void CollectXRay();
	void CollectInvisibility();
	

	void ToggleInvisibility();

	TObjectPtr<ACustomGameState> gs;

	//spawned in the xray spot
	AActor* XRayCollectible;
	//spawned in the invisibility spot
	AActor* InvisibilityCollectible;
	//spawned in the movement ability spot
	AActor* MovementAbilityCollectible;
	//spawned in the teleport ability spot
	AActor* TeleportAbilityCollectible;


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
