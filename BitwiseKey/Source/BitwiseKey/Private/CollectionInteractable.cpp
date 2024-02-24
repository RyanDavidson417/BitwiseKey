// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectionInteractable.h"
#include "BitwiseGameState.h"
#include "BitwiseGameMode.h"
#include "Components/AudioComponent.h" 
#include "Interactables/ASpawnPowerup.h"
#include "BitwiseKey/BitwiseKey.h"
#include "Kismet/GameplayStatics.h" 
#include "BWK_RandomizerBase.h"
#include "Components/AudioComponent.h" 

UCollectionInteractable::UCollectionInteractable()
{
}

void UCollectionInteractable::BeginPlay()
{
	gm = GetWorld()->GetAuthGameMode<ABitwiseGameMode>();
	gs = Cast<ABitwiseGameState>(gm->GameState);

	CollectionSound = GetOwner()->FindComponentByClass<UAudioComponent>(); 

	StartZ = GetOwner()->GetActorLocation().Z;

	PodMesh =  Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));

	UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(Material, GetOwner());

	DynMaterial->SetVectorParameterValue(FName("Emissive color 01"), PowerupColor);

	PodMesh->SetMaterial(2, DynMaterial);

	WARN("podmesh: %s ", *PodMesh->GetName())


	//if we wanted different collection sounds for different powerups, we'd probably set those on the powerup prefab, then copy the data over here

	/*
	UMaterialInstanceDynamic* GlassMaterial = Cast<UMaterialInstanceDynamic>(PodMesh->GetMaterial(2));

	if (IsValid(GlassMaterial)) {
		GlassMaterial->

	}
	else {
		WARN("nope")
	}*/

}

void UCollectionInteractable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	float timeInSeconds = UGameplayStatics::GetTimeSeconds(GetWorld());
	float newZ = StartZ + ((FMath::Sin(timeInSeconds) +1) *50 );
	GetOwner()->SetActorLocation(FVector(GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y, newZ));

}

void UCollectionInteractable::Interact(APlayerController* playerController)
{
	if (IsValid(CollectionSound)) {
		CollectionSound->Play();
	}
	else {
		WARN("collection sound not valid")

	}

	//play sound
	//CollectionSound->Play();
	if (IsValid(SpawnPoint)) {
		if (IsValid(SpawnPoint->CollectionSound)) {
			SpawnPoint->CollectionSound->Play();

		}
		else {
			WARN("collection sound not valid")
		}
	}
	else {
		WARN("spawn point not valid")

	}

	if (Randomizer) {

		Randomizer->RemoveItemFromPlacedActors(GetOwner());
	}

	// while (CollectionSound->IsPlaying()) {	}//infinite loop lmao

	GetOwner()->Destroy();
}
