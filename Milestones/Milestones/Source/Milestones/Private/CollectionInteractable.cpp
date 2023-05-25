// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectionInteractable.h"
#include "CustomGameState.h"
#include "CustomGameMode.h"

UCollectionInteractable::UCollectionInteractable()
{
}

void UCollectionInteractable::BeginPlay()
{
	gm = GetWorld()->GetAuthGameMode<ACustomGameMode>();
	gs = Cast<ACustomGameState>(gm->GameState);
}

void UCollectionInteractable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
}

void UCollectionInteractable::Interact(APlayerController* playerController)
{

	//ACustomGameMode* gm1 = (ACustomGameMode*)GetWorld()->GetAuthGameMode();
	UE_LOG(LogTemp, Warning, TEXT("Collected object"));
	//
	if (IsValid(gm)) {
		UE_LOG(LogTemp, Warning, TEXT("called object collection from base interactable - this shouldn't happen"));

		//gm1->CollectXRay();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("gm not valid"));
	}


}
