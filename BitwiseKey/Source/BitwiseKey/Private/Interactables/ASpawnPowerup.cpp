// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Interactables/ASpawnPowerup.h"
#include "BitwiseGameState.h"
#include "Components/AudioComponent.h" 
#include "Interactables/XRayVision.h"  
#include "BitwiseGameMode.h"
#include "Math/Rotator.h"
#include "CollectionInteractable.h"
#include "Interactables/RandomItemSpawner.h"
#include "Math/Vector.h" 
#include "CollectionInteractable.h"
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


}

// Called when the game starts or when spawned
void ASpawnPowerup::BeginPlay()
{
	gm = GetWorld()->GetAuthGameMode<ABitwiseGameMode>();
	gs = Cast<ABitwiseGameState>(gm->GameState);
	
	FActorSpawnParameters SpawnInfo;

	FRotator myRot(0, 0, 0);
	FVector myPos(0, 0, 0);

	CollectionSound = FindComponentByClass<UAudioComponent>();

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


