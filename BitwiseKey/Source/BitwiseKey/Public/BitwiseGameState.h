// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "BitwiseGameState.generated.h"

/**
 * 
 */

UENUM(BlueprintType) 
enum class EPowerUpName : uint8
{
	PE_XRay UMETA(DisplayName="XRay"),
	PE_Invisibility UMETA(DisplayName = "Invisibility"),
	PE_SpeedBoost UMETA(DisplayName = "SpeedBoost"),
	PE_JumpBoost UMETA(DisplayName = "JumpBoost"),
}; //yet to decide whether the mvement ability will be wall climb related or a grapple


USTRUCT(BlueprintType)
struct FPowerupStruct
{
	GENERATED_BODY()

	//generalizedRef genRef
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
	EPowerUpName name;
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


UCLASS()
class BITWISEKEY_API ABitwiseGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	ABitwiseGameState();

	bool GetStaminaActive();
	bool GetStaminaAbilityHeld();
	void BeginPlay() override;
	

private:

	void BuildPowerupMap();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timer")
	float gameTimer = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
	FPowerupStruct XRayStruct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
	FPowerupStruct InvisibilityStruct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
	FPowerupStruct SpeedBoostStruct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
	FPowerupStruct JumpBoostStruct;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Powerups")
	TMap<EPowerUpName, FPowerupStruct> PowerupMap;

	//DEPRECATED: the means by which I was storing whether the player collected powerups before I refac'd to structs
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectibles")
	//bool bHasXray;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectibles")
	//bool bHasSpeedBoost;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectibles")
	//bool bHasJumpBoost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectibles")
	bool bHasStaminaAbility;	

	//invisibility 
	
	//stamina	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Powerups")
		bool bPlayerIsUsingStamina;


};
