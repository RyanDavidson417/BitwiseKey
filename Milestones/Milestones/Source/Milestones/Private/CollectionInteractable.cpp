// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectionInteractable.h"
#include "CustomGameState.h"
#include "CustomGameMode.h"
#include "Components/AudioComponent.h" 

UCollectionInteractable::UCollectionInteractable()
{
}

void UCollectionInteractable::BeginPlay()
{
	gm = GetWorld()->GetAuthGameMode<ACustomGameMode>();
	gs = Cast<ACustomGameState>(gm->GameState);

	CollectionSound = GetOwner()->FindComponentByClass<UAudioComponent>(); 
}

void UCollectionInteractable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
}

void UCollectionInteractable::Interact(APlayerController* playerController)
{
	//play sound
	CollectionSound->Play();
	

}
