// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/XRayVision.h"  
#include "Core/BitwiseGameMode.h"

UXRayVision::UXRayVision()
{
}



void UXRayVision::Interact_Implementation(APlayerController* playerController)
{
	//
	CollectPowerup(playerController);
	Super::Interact(playerController);
}

void UXRayVision::CollectPowerup(APlayerController* playerController)
{
	if (IsValid(gm)) {
		gm->CollectXRay();
	}
	else {
		WARN("gamestate not valid")
	}

}

