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

	UE_LOG(LogTemp, Warning, TEXT("Collected object"));
	TObjectPtr<ACustomGameMode> gm = GetWorld()->GetAuthGameMode<ACustomGameMode>(); //should maybe do this as a variable in the .h
	gm->CollectXRay();

}
