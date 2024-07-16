// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelObjects/CollectionInteractable.h"
#include "Core/BitwiseGameState.h"
#include "Core/BitwiseGameMode.h"
#include "Components/AudioComponent.h" 
#include "Interactables/ASpawnPowerup.h"
#include "BitwiseKey/BitwiseKey.h"
#include "Kismet/GameplayStatics.h" 
#include "LevelObjects/BWK_RandomizerBase.h"
#include "Components/AudioComponent.h" 

UCollectionInteractable::UCollectionInteractable()
{
}

void UCollectionInteractable::BeginPlay()
{
	Super::BeginPlay();
	gm = GetWorld()->GetAuthGameMode<ABitwiseGameMode>();
	gs = Cast<ABitwiseGameState>(gm->GameState);

	CollectionSound = GetOwner()->FindComponentByClass<UAudioComponent>(); 

	StartZ = GetOwner()->GetActorLocation().Z;




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

void UCollectionInteractable::Interact_Implementation(APlayerController* playerController)
{

	if (Randomizer) {

		Randomizer->RemoveItemFromPlacedActors(GetOwner());
	}

	GetOwner()->Destroy();
}
