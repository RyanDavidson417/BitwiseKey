// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/XRayVision.h"
#include "CustomGameMode.h"

UXRayVision::UXRayVision()
{
}



void UXRayVision::Interact(APlayerController* playerController)
{
	UE_LOG(LogTemp, Warning, TEXT("Collected object"));
	//
	if (IsValid(gm)) {
		gm->CollectXRay();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("gm not valid"));
	}
}
