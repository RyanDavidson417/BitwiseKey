// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/DoubleJump.h"
#include "PlayerCharacter.h"

void UDoubleJump::CollectPowerup(APlayerController* playerController)
{
	if (IsValid(gs)) {
		gs->DoubleJumpData->bCollected = true;
		playerController->GetCharacter()->JumpMaxCount
			= gs->DoubleJumpData->ActiveValue;
	}
}

void UDoubleJump::Reset()
{
		UE_LOG(LogTemp, Warning, TEXT("jump reset"))
	if (IsValid(gs)) {
		gs->DoubleJumpData->bCollected = false;


		if (IsValid(MPlayerController)) {
			MPlayerController->GetCharacter()->JumpMaxCount
				= gs->DoubleJumpData->defaultValue;
		}
	}
}
