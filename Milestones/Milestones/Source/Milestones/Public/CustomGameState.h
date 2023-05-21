// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "CustomGameState.generated.h"

/**
 * 
 */
UCLASS()
class MILESTONES_API ACustomGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	ACustomGameState();

private:

public:
	float gameTimer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectibles")
	bool hasXray;
	bool hasGrapple;
	bool hasWallGrip;
	bool hasTeleport;
	bool hasEnemyDisrupt;

};
