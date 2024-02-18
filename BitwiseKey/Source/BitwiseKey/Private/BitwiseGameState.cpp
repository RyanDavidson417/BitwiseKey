// Fill out your copyright notice in the Description page of Project Settings.


#include "BitwiseGameState.h"


ABitwiseGameState::ABitwiseGameState()
{
	BuildPowerupMap();
}

void ABitwiseGameState::ResetGameState()
{
	for (TPair<EPowerUpName, FPowerupStruct> pair : PowerupMap) {
		pair.Value.bCollected = false;
		pair.Value.bEnabled = false;
	}

}

void ABitwiseGameState::BuildPowerupMap() 
{
	PowerupMap.Add(EPowerUpName::PE_XRay, XRayStruct);
	PowerupMap.Add(EPowerUpName::PE_Invisibility, InvisibilityStruct);
	PowerupMap.Add(EPowerUpName::PE_SpeedBoost, SpeedBoostStruct);
	PowerupMap.Add(EPowerUpName::PE_JumpBoost, JumpBoostStruct);
}



bool ABitwiseGameState::GetStaminaActive() 
{
	for (TPair<EPowerUpName, FPowerupStruct> pair : PowerupMap)  {
		//if any element in the map is a stamina ability AND is active, return true
		if (pair.Value.bIsStaminaAbility && pair.Value.bEnabled) { 
			return true;
		}
	}
	//if we get through the whole map without finding anything, return false
	return false;
}

bool ABitwiseGameState::GetStaminaAbilityHeld()
{
	for (TPair<EPowerUpName, FPowerupStruct> pair : PowerupMap) {
		//if any element in the map is a stamina ability AND is active, return true
		if (pair.Value.bIsStaminaAbility && pair.Value.bCollected) {
			return true;
		}
	}
	return false;
}

void ABitwiseGameState::BeginPlay()
{
	Super::BeginPlay();
	BuildPowerupMap();


}


