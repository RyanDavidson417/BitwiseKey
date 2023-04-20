// Fill out your copyright notice in the Description page of Project Settings.


#include "Lab03/Lab03SceneComponent.h"

// Sets default values for this component's properties
ULab03SceneComponent::ULab03SceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULab03SceneComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void ULab03SceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	currRotation = GetWorld()->GetTimeSeconds() * speed;
	GetOwner()->SetActorRotation(FRotator(0, currRotation, 0 ));
	UE_LOG(LogTemp, Warning, TEXT("Current Rotation: "));

	// ...
}

// Function that defines default behavior that occurs when the event fires
// Do not implement OnInteracted() and the implementation, just the implementation
void ULab03SceneComponent::OnInteracted_Implementation()
{
	OnInteractedBehavior();
}

// Because BlueprintNativeEvent can't be virtual, have the native event call a virtual function.
// This allows child class to override virtual for different / additional functionality.
void ULab03SceneComponent::OnInteractedBehavior()
{
	// Print the name of the actor
	UE_LOG(LogTemp, Warning, TEXT("AExampleEventActor: %s"), *GetName());
}
