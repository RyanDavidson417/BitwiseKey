// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Interactables/ASpawnPowerup.h"
#include "Core/BitwiseGameState.h"
#include "Components/AudioComponent.h" 
#include "Interactables/XRayVision.h"  
#include "Core/BitwiseGameMode.h"
#include "Engine/EngineTypes.h" 
#include "Math/Rotator.h"
#include "LevelObjects/CollectionInteractable.h"
#include "Interactables/RandomItemSpawner.h"
#include "Math/Vector.h" 
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


	CollectionSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("CollectionSoundComponent"));
	TrillSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("TrillSoundComponent"));

}

// Called when the game starts or when spawned
void ASpawnPowerup::BeginPlay()
{
	gm = GetWorld()->GetAuthGameMode<ABitwiseGameMode>();
	gs = Cast<ABitwiseGameState>(gm->GameState);
	
	CollectionSoundComponent->OnAudioFinished.AddDynamic(this, &ASpawnPowerup::PlayTrillSound);

	FActorSpawnParameters SpawnInfo;

	FRotator myRot(0, 0, 0);
	FVector myPos(0, 0, 0);


}

void ASpawnPowerup::StartTrillSoundTimer()
{
	LOG("starting timer")
		//PlayTrillSound();
		//GetWorldTimerManager().SetTimer(
		//	AudioTimerHandle, this, &ASpawnPowerup::PlayTrillSound,
		//	CollectionSoundComponent->Sound->Duration, false);
		//AudioTimerHandle, CollectionSoundComponent->Sound->Duration, false);
	// &ASpawnPowerup::PlayTrillSound
}

void ASpawnPowerup::PlayTrillSound()
{
	LOG("playing trill sound YIPPEE")
	if (IsValid(TrillSoundComponent)) {
		if (IsValid(TrillSoundComponent->Sound)) {

			TrillSoundComponent->Play();
		}
		else {
			WARN("trill sound clip not valid")
		}
	}
	else {
		WARN("trill sound component not valid")
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


