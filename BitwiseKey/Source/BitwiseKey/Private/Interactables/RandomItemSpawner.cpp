// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/RandomItemSpawner.h"

// Sets default values
ARandomItemSpawner::ARandomItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARandomItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARandomItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

