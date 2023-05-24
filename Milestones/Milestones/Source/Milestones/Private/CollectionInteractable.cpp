// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectionInteractable.h"
#include "CustomGameMode.h"

UCollectionInteractable::UCollectionInteractable()
{
}

void UCollectionInteractable::BeginPlay()
{
}

void UCollectionInteractable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
}

void UCollectionInteractable::Interact(APlayerController* playerController)
{
	TObjectPtr<class ACustomGameMode> gm1 = GetWorld()->GetAuthGameMode<ACustomGameMode>();

	//ACustomGameMode* gm1 = (ACustomGameMode*)GetWorld()->GetAuthGameMode();
	UE_LOG(LogTemp, Warning, TEXT("Collected object"));
	//
	if (IsValid(gm1)) {
		gm1->CollectXRay();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("gm not valid"));
	}


}
