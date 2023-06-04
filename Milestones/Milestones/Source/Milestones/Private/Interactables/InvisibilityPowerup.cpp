// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/InvisibilityPowerup.h"
#include "CustomGameMode.h"

UInvisibilityPowerup::UInvisibilityPowerup()
{
}

void UInvisibilityPowerup::Interact(APlayerController* playerController)
{
	Super::Interact(playerController);//called at the end, cause it also destroys the object
	if (IsValid(gm)) {
		gm->CollectInvisibility();
	}
	

}
