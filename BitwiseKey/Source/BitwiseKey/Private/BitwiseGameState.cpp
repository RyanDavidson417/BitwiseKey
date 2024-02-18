// Fill out your copyright notice in the Description page of Project Settings.


#include "BitwiseGameState.h"


ABitwiseGameState::ABitwiseGameState()
{
}


bool ABitwiseGameState::GetStaminaActive() 
{
	for (TPair<EPowerUpName, FPowerupStruct> pair : PowerupMap)  {
		//if any element in the map is a stamina ability AND is active, return true
		if (pair.Value.bIsStaminaAbility && pair.Value.bIsActive) { 
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


