// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "CustomGameState.generated.h"

/**
 * 
 */

UENUM(BlueprintType) 
enum class EPowerUp : uint8
{
	PE_XRay UMETA(DisplayName="XRay"),
	PE_Invisibility UMETA(DisplayName = "Invisibility"),
	PE_Teleport UMETA(DisplayName = "Teleport"),
	PE_Movement UMETA(DisplayName = "Movement"),
}; //yet to decide whether the mvement ability will be wall climb related or a grapple



UCLASS()
class BITWISEKEY_API ACustomGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	ACustomGameState();

private:

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timer")
	float gameTimer = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectibles")
	bool hasXray;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectibles")
	bool hasWallGrip;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectibles")
	bool hasTeleport;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectibles")
	bool hasInvisibility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectibles")
	EPowerUp PowerupEnum;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectibles")
		TArray<EPowerUp> EA_PowerupOrder;

	//invisibility 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectibles")
		bool bPlayerIsInvisible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
		float CurrentInvisCharge = 0;



};
