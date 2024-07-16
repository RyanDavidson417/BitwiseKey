// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/PowerupCollectibleBase.h"
#include "Components/AudioComponent.h" 
#include "GameFramework/Actor.h" 
#include "Interactables/ASpawnPowerup.h"
#include "Core/BitwiseGameMode.h"

void UPowerupCollectibleBase::CollectPowerup(APlayerController* playerController)
{
	WARN("default implementation called")
}

void UPowerupCollectibleBase::Interact_Implementation(APlayerController* PlayerController)
{
	MPlayerController = PlayerController;

	CollectPowerup(PlayerController);



	//play sound
	//CollectionSound->Play();
	if (IsValid(SpawnPoint)) {
		SpawnPoint->StartTrillSoundTimer();
			//AudioTimerHandle, this, &ASpawnPowerup::PlayTrillSound,
			// //SpawnPoint->TrillSoundComponent->Sound->Duration, false);
		if (IsValid(SpawnPoint->CollectionSoundComponent)) {
			LOG("playing sound")
			SpawnPoint->CollectionSoundComponent->Play();

		}
		else {
			WARN("collection sound not valid")
		}
	}
	else {
		WARN("spawn point not valid")

	}

	Super::Interact_Implementation(PlayerController);//call at the end as this destroys the object
}

void UPowerupCollectibleBase::Reset()
{
	LOG("FUUUUUUUUUUU")
}

void UPowerupCollectibleBase::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(gm)) {
		gm->D_OnReset.AddDynamic(this, &UPowerupCollectibleBase::Reset);

	}

	PodMesh = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));

	UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(Material, GetOwner());

	DynMaterial->SetVectorParameterValue(FName("EmissiveColor"), PowerupColor);

	LOG("COLOR: %s", *PowerupColor.ToString())

	PodMesh->SetMaterial(2, DynMaterial);

	//WARN("podmesh: %s ", *PodMesh->GetName())

}
