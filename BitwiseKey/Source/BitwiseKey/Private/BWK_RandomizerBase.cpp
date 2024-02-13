// Fill out your copyright notice in the Description page of Project Settings.

#include "BWK_RandomizerBase.h"
#include "CustomGameMode.h"
#include "CustomGameState.h"
#include "../BitwiseKey.h"
#include "Kismet//KismetMathLibrary.h"

// Sets default values
ABWK_RandomizerBase::ABWK_RandomizerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void ABWK_RandomizerBase::BeginPlay()
{
	Super::BeginPlay();

	gm = GetWorld()->GetAuthGameMode<ACustomGameMode>();

	RandomizeOrder();
	PlaceItems();
	gm->D_OnReset.AddDynamic(this, &ABWK_RandomizerBase::ResetItems);
		//
}


void ABWK_RandomizerBase::RandomizeOrder()
{

	// -- RANDOMIZE ORDER OF ITEMS --
	//if we ever wanted to place items without randomizing, we could surround this region with a bool 
	TArray<TSubclassOf<AActor>> RandomizedArray; // create a new (blank) array for us to copy the items into
	int NumOfItems = ItemArray.Num();
	//RandomizedArray.SetNum(NumOfItems); //set the size of the new array equal to our current item array

	for (int i = 0; i < NumOfItems; i++) {

		//check if it's null? or maybe we still want to re-randomize if it's null and check that if it's placed


		int rand = FMath::RandRange(0, NumOfItems- i - 1);
		LOG("ARRAY SPOT: %d, num of items: %d", rand, NumOfItems)
		//FMath::RandRange(0, NumOfItems - i - 1);//generate a random number from the number of loops we've had up 
		RandomizedArray.Add(ItemArray[rand]);
		ItemArray.RemoveAt(rand);//necessary because as we remove items from the array we don't want them drawn again
		//might be worth removing if we edit funcitonality to allow for different randomization rules
		//such as repeating 

	}
	ItemArray = RandomizedArray;
}

void ABWK_RandomizerBase::PlaceItems()
{

	LOG("HELLO2")
	// -- PLACE ITEMS --

	int NumOfSpawns = SpawnerArray.Num();
	for (int i = 0; i < NumOfSpawns; i++) {

		AActor* PlacedActor;

		if (ItemArray[i]) {//if item array at i is not null, this DOES allow us to place empty items
			if (PlacedActor = GetWorld()->SpawnActor<AActor>(
				ItemArray[i], SpawnerArray[i]->GetActorLocation(),
				SpawnerArray[i]->GetActorRotation())) {

					PlacedActors.Add(PlacedActor);
			}

			LOG("HELLO")

			//XRayCollectible, PowerupSpawnLocations[i]->GetActorLocation(), 
			//PowerupSpawnLocations[i]->GetActorRotation());

		}
	}
	LOG("ARRAY placed")
}


void ABWK_RandomizerBase::ResetItems()
{
	LOG("HELLO3")
	for (TObjectPtr<AActor> actor : PlacedActors) {
		if (actor) {
			GetWorld()->DestroyActor(actor);
		}
	}

	RandomizeOrder();
	PlaceItems();
}

void ABWK_RandomizerBase::RemoveItemFromPlacedActors(TObjectPtr<AActor> actor)
{
	if (PlacedActors.Contains(actor)) {
		PlacedActors.Remove(actor);
	}
}


// Called every frame
void ABWK_RandomizerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

