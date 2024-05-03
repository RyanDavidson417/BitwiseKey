// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Interactables/ASpawnPowerup.h"
#include "Core/BitwiseGameState.h"
#include "Components/AudioComponent.h" 
#include "Interactables/XRayVision.h"  
#include "Core/BitwiseGameMode.h"
#include "Math/Rotator.h"
#include "LevelObjects/CollectionInteractable.h"
#include "Interactables/RandomItemSpawner.h"
#include "Math/Vector.h" 
#include "UObject/WeakObjectPtr.h"
#include "Kismet/GameplayStatics.h"
#include "LevelObjects/CollectionInteractable.h"
#include "../BitwiseKey.h"
#include "Engine/World.h" 

/*struct FActorSpawnParameters;
class FRotator;
class FVector;*/
//class UXrayVision;


// Sets default values
ASpawnPowerup::ASpawnPowerup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	CollectionAudioComponent = CreateDefaultSubobject<UAudioComponent>("CollectionAudioComponent");
	TrillAudioComponent = CreateDefaultSubobject<UAudioComponent>("TrillAudioComponent");


}

// Called when the game starts or when spawned
void ASpawnPowerup::BeginPlay()
{
	CollectionAudioComponent->OnAudioFinished.AddUniqueDynamic(this, &ASpawnPowerup::PlayTrillSound);
	//OnCollectionSoundFinishedDelegate.

	CollectionAudioComponent->Sound = CollectionAudioClip;
	TrillAudioComponent->Sound = TrillAudioClip;

	gm = GetWorld()->GetAuthGameMode<ABitwiseGameMode>();
	gs = Cast<ABitwiseGameState>(gm->GameState);
	
	FActorSpawnParameters SpawnInfo;

	FRotator myRot(0, 0, 0);
	FVector myPos(0, 0, 0);


}

void ASpawnPowerup::PlayTrillSound()
{
	LOG("PLAYING TRILL SOUND YIPPEEE")
	if (IsValid(TrillAudioClip)) {
		UGameplayStatics::PlaySound2D(this, TrillAudioClip);
	}
}

void ASpawnPowerup::Tick(float DeltaTime)
{
}

void ASpawnPowerup::Spawn(TSubclassOf<AActor*> actor)
{
	/*
	if (AActor* newActor = Cast<AActor>(actor)) {
		WARN("CAST YIPPEE")
			//UCollectionInteractable* powerup = newActor->FindComponentByClass<UCollectionInteractable>();
	}*/
	
	//if(UCollectionInteractable powerup )
}


