// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BitwiseGameState.h"
#include "BitwiseKey/BitwiseKey.h"
#include "LevelObjects/PowerupDataBase.h"


ABitwiseGameState::ABitwiseGameState()
{
	BuildPowerupMap();
}

void ABitwiseGameState::ResetGameState()
{
	for (UPowerupDataBase* powerup : PowerupDataArray) {
		powerup->bCollected = false;
		powerup->bEnabled = false;
	}


	
}

void ABitwiseGameState::BuildPowerupMap() 
{
	PowerupDataArray.Add(XRayData);
	PowerupDataArray.Add(InvisibilityData);
	PowerupDataArray.Add(SpeedBoostData);
	PowerupDataArray.Add(JumpBoostData);
	PowerupDataArray.Add(DoubleJumpData);


}



bool ABitwiseGameState::GetPlayerIsUsingStamina() 
{
	for(UPowerupDataBase* powerup: PowerupDataArray) {
		//if any element in the map is a stamina ability AND is active, return true
		if (powerup->bIsStaminaAbility && powerup->bEnabled) {
			return true;
		}
	}
	//if we get through the whole map without finding anything, return false
	return false;
}

bool ABitwiseGameState::GetHasStaminaAbility()
{
	for (UPowerupDataBase* powerup : PowerupDataArray) {
		//if any element in the map is a stamina ability AND is active, return true
		if (powerup->bIsStaminaAbility && powerup->bCollected) {
			return true;
		}
	}
	return false;
}

void ABitwiseGameState::BeginPlay()
{
	Super::BeginPlay();
	
	BuildPowerupMap();
	ResetGameState();//necessary because otherwise the dataAsset's data would persist after rebooting game



}


