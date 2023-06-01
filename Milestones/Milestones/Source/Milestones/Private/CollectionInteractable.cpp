// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectionInteractable.h"
#include "CustomGameState.h"
#include "CustomGameMode.h"
#include "Milestones/Milestones.h"
#include "Kismet/GameplayStatics.h" 
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
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	float timeInSeconds = UGameplayStatics::GetTimeSeconds(GetWorld());
	float newZ = GetOwner()->GetActorLocation().Z + ((FMath::Sin(timeInSeconds)) );
	GetOwner()->SetActorLocation(FVector(GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y, newZ));

}

void UCollectionInteractable::Interact(APlayerController* playerController)
{
	//play sound
	CollectionSound->Play();
	

}
