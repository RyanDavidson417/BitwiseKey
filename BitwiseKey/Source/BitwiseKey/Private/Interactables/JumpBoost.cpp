// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/JumpBoost.h"
#include "PlayerCharacter.h"

void UJumpBoost::CollectPowerup(APlayerController* playerController)
{
	if (IsValid(gs)) {
		playerController->GetCharacter()->GetCharacterMovement()->JumpZVelocity
			= gs->JumpBoostData->ActiveValue;
	}
}

void UJumpBoost::Reset()
{
	if (IsValid(gs)) {
		if (IsValid(MPlayerController)) {
			MPlayerController->GetCharacter()->GetCharacterMovement()->JumpZVelocity
				= gs->JumpBoostData->defaultValue;
		}
	}
}
