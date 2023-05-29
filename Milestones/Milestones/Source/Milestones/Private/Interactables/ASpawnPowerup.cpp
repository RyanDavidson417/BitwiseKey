// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/ASpawnPowerup.h"
#include "CustomGameState.h"
#include "CustomGameMode.h"

// Sets default values
AASpawnPowerup::AASpawnPowerup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AASpawnPowerup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AASpawnPowerup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

