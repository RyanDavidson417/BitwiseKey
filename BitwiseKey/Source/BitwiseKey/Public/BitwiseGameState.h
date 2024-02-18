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


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPowerUpName name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCollected;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsStaminaAbility;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsActive; //a possible concern is that since this var is accessed through a map of the powerups, 
	//	and accessed very frequently, the cost of repeatedly iterating over that map could pose performance
	//  issues. the map will not likely be any larger than 10 powerups (probably half that), so it hopefully
	//  won't be an issue. but it's something to consider and keep an eye out for.
	//	this is especially a concern with invisibility, which gets checked almost constantly (enemies do so every
	//	tick that they see the player). it could be useful to just remake the bPlayerIsinvisble variable and set 
	//	them equal to one another somehow

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Powerups")
	FPowerupStruct XRayStruct;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Powerups")
	FPowerupStruct InvisibilityStruct;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Powerups")
	FPowerupStruct SpeedBoostStruct;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Powerups")
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
