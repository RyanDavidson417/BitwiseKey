// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/InvisibilityPowerup.h"
#include "Core/BitwiseGameMode.h"

UInvisibilityPowerup::UInvisibilityPowerup()
{
}

void UInvisibilityPowerup::Interact_Implementation(APlayerController* playerController)
{
	Super::Interact(playerController);//called at the end, cause it also destroys the object
}

void UInvisibilityPowerup::CollectPowerup(APlayerController* playerController)
{
	if (IsValid(gm)) {
		gm->CollectInvisibility();

	}
	else {
		WARN("gamestate not valid")
	}
}

