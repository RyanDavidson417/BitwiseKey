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

};
