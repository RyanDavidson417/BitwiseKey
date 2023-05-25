// Fill out your copyright notice in the Description page of Project Settings.


#include "inClass/QuestSystem/Objectives/ObjReachDestination.h"

#include "Components/ShapeComponent.h"
#include "Lab06/Lab06MovementPawn.h"

void UObjReachDestination::ActivateObjective()
{
	Super::ActivateObjective();

	Destination->OnComponentBeginOverlap.AddDynamic(this, &UObjReachDestination::ReachedDestination);

}

bool UObjReachDestination::GetIsComplete() const
{
	//this objective is complete if we've reached our destination
	return bReachedDestination;
}

void UObjReachDestination::ReachedDestination(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: GET FILEPATH FOR THE PLAYER
	//if overlapped by the player
	if (Cast<ALab06MovementPawn>(OtherActor)) {
		UE_LOG(LogTemp, Warning, TEXT("character reached destination: %s"), *Destination->GetName());

		//clearing all listenersx from delegate
		Destination->OnComponentBeginOverlap.Clear();

		//the destination has been reached
		bReachedDestination = true;

		CompleteObjective();
	}
}
