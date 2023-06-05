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

	StartZ = GetOwner()->GetActorLocation().Z;

	PodMesh =  Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));

	UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(Material, GetOwner());

	DynMaterial->SetVectorParameterValue(FName("Emissive color 01"), PowerupColor);

	PodMesh->SetMaterial(2, DynMaterial);

	WARN("podmesh: %s ", *PodMesh->GetName())

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

void UCollectionInteractable::Interact(APlayerController* playerController)
{
	//play sound
	CollectionSound->Play();


	// while (CollectionSound->IsPlaying()) {	}//infinite loop lmao

	//GetOwner()->Destroy();
}
