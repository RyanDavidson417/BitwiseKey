// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/SpeedBoost.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter.h"

void USpeedBoost::CollectPowerup(APlayerController* playerController)
{
	if (IsValid(gs)) {
		gs->SpeedBoostData->bCollected = true;
		if (gs->SpeedBoostData->bPassive) { //if it's passive, just set it automatically
			playerController->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed
				= gs->SpeedBoostData->ActiveValue;
		}
		else {
			if (gs->SpeedBoostData->bIsStaminaAbility) {//double check that it's a stamina ability
				//
			}
			else {
				WARN("speed boost is neither passive nor tied to stamina. idk what you want me to do here (you probably just forgot to set one of those vals")
			}
		}
	}
}
//
//void USpeedBoost::Reset()
//{
//	LOG("receiving reset")
//	if (IsValid(gs)) {
//
//		gs->SpeedBoostData->bCollected = false;
//
//		if (IsValid(MPlayerController)) {
//			MPlayerController->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed
//				= gs->SpeedBoostData->defaultValue;
//		}
//	}
//}
