// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectionInteractable.h"

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

}
