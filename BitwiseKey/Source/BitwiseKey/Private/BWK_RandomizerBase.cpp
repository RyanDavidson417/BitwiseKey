// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomGameMode.h"
#include "CustomGameState.h"
#include "../BitwiseKey.h"
#include "BWK_RandomizerBase.h"

// Sets default values
ABWK_RandomizerBase::ABWK_RandomizerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABWK_RandomizerBase::RandomizeOrder()
{
	
	TArray<TSubclassOf<AActor>> RandomizedArray; // create a new (blank) array for us to copy the items into
	int NumOfItems = ItemArray.Num();
	//RandomizedArray.SetNum(NumOfItems); //set the size of the new array equal to our current item array
	
	for (int i = 0; i < NumOfItems; i++) {

		//check if it's null? or maybe we still want to re-randomize if it's null and check that if it's placed

		int rand = FMath::RandRange(0, NumOfItems - i - 1);//generate a random number from the number of loops we've had up 
		RandomizedArray.Add(ItemArray[rand]);
		ItemArray.RemoveAt(rand);//unsure why we need to do this, remove?

	}
	ItemArray.Empty();

	ItemArray = RandomizedArray;
}

void ABWK_RandomizerBase::PlaceItems()
{
	int NumOfSpawns = SpawnerArray.Num();

	for (int i = 0; i < NumOfSpawns; i++) {

		AActor* PlacedActor;

		LOG("HELLO")


		if (ItemArray[i]) {//if item array at i is not null
				PlacedActor = GetWorld()->SpawnActor<AActor>(
					ItemArray[i], SpawnerArray[i]->GetActorLocation(),
					SpawnerArray[i]->GetActorRotation());

			LOG("HELLO")

			//XRayCollectible, PowerupSpawnLocations[i]->GetActorLocation(), 
			//PowerupSpawnLocations[i]->GetActorRotation());

		}
	}

}

// Called when the game starts or when spawned
void ABWK_RandomizerBase::BeginPlay()
{
	Super::BeginPlay();

	RandomizeOrder();
	PlaceItems();
		
}

// Called every frame
void ABWK_RandomizerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

