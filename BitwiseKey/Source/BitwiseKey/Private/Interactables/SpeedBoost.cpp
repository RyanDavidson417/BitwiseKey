// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/SpeedBoost.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter.h"

void USpeedBoost::CollectPowerup(APlayerController* playerController)
{
	if (IsValid(gs)) {
		playerController->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed
			= gs->SpeedBoostData->ActiveValue;
	}
}

void USpeedBoost::Reset()
{
	if (IsValid(gs)) {
		if (IsValid(MPlayerController)) {
			MPlayerController->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed
				= gs->SpeedBoostData->defaultValue;
		}
	}
}
