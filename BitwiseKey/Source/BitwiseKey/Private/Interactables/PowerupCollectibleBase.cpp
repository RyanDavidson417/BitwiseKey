// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/PowerupCollectibleBase.h"
#include "BitwiseGameMode.h"

void UPowerupCollectibleBase::CollectPowerup(APlayerController* playerController)
{
	WARN("default implementation called")
}

void UPowerupCollectibleBase::Interact(APlayerController* PlayerController)
{
	MPlayerController = PlayerController;

	CollectPowerup(PlayerController);

	Super::Interact(PlayerController);//call at the end as this destroys the object
}

void UPowerupCollectibleBase::Reset()
{
}

void UPowerupCollectibleBase::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(gm)) {
		gm->D_OnReset.AddDynamic(this, &UPowerupCollectibleBase::Reset);

	}
}
