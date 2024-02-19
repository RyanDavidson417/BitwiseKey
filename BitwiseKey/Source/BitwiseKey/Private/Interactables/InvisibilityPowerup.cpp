// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/InvisibilityPowerup.h"
#include "BitwiseGameMode.h"

UInvisibilityPowerup::UInvisibilityPowerup()
{
}

void UInvisibilityPowerup::Interact(APlayerController* playerController)
{
	Super::Interact(playerController);//called at the end, cause it also destroys the object
}

void UInvisibilityPowerup::CollectPowerup(APlayerController* playerController)
{
	if (IsValid(gs)) {

		gs->InvisibilityData->bCollected = true;
	}
	else {
		WARN("gamestate not valid")
	}
}

