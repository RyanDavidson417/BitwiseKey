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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectibles")
	bool hasGrapple;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectibles")
	bool hasWallGrip;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectibles")
	bool hasTeleport;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectibles")
	bool hasInvisibility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectibles")
	bool bPlayerIsInvisible;

};
