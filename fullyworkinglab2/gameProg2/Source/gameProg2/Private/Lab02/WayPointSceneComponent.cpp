// Fill out your copyright notice in the Description page of Project Settings.


#include "Lab02/WayPointSceneComponent.h"
#include "../../Lab02/BPLibInClass.h"

#include "gameProg2/Lab02/BPLibInClass.h"

// Sets default values for this component's properties
UWayPointSceneComponent::UWayPointSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWayPointSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWayPointSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FRotator NewRotation = GetOwner()->GetActorRotation();
	
	float RunningTime = GetOwner()->GetGameTimeSinceCreation();
	
	GetOwner()->SetActorLocation(UBPLibInClass::MoveTowards(CurrentLocation, waypoints[WPIndex], speed));

		
	if(FVector::Distance(CurrentLocation, waypoints[WPIndex]) <= 1)
	{
		WPIndex = (WPIndex + 1) % waypoints.Num();
	}
	
	// ...
}

