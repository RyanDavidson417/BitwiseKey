// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/XRayVision.h"  
#include "Core/BitwiseGameMode.h"

UXRayVision::UXRayVision()
{
}



void UXRayVision::Interact_Implementation(APlayerController* playerController)
{
	//
	Super::Interact_Implementation(playerController);
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

