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

	//the default value of the relevant stat when this powerup is active
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
	float defaultValue;
	//the value of the relevant stat when this powerup is active
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
	float ActiveValue;

};
