// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PowerupDataBase.generated.h"

/**
 * 
 */
UCLASS()
class BITWISEKEY_API UPowerupDataBase : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName name;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
	bool bCollected;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
	bool bIsStaminaAbility;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
	bool bEnabled;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
	bool bPassive;


	//the default value of the relevant stat when this powerup is active
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
	float defaultValue;
	//the value of the relevant stat when this powerup is active
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
	float ActiveValue;


};
