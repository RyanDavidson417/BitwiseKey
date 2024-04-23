// Fill out your copyright notice in the Description page of Project Settings.

#include "BWK_RandomizerBase.h"
#include "BitwiseGameMode.h"
#include "BitwiseGameState.h"
#include "Interactables/ASpawnPowerup.h"
#include "Interactables/PowerupCollectibleBase.h"
#include "../BitwiseKey.h"
#include "LevelPrefabBase.h"
#include "Engine/GameInstance.h"
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

	gm = GetWorld()->GetAuthGameMode<ABitwiseGameMode>();

	RandomizeOrder();
	PlaceItems();
	gm->D_OnReset.AddDynamic(this, &ABWK_RandomizerBase::ResetItems);
		//
}


void ABWK_RandomizerBase::ReceiveOnItemsPlaced_Implementation()
{//no c++ behavior
}

void ABWK_RandomizerBase::RandomizeOrder()
{
	//LOG("name: %s", *GetName())

	// -- RANDOMIZE ORDER OF ITEMS --
	//if we ever wanted to place items without randomizing, we could surround this region with a bool 
	TArray<TSubclassOf<AActor>> RandomizedArray; // create a new (blank) array for us to copy the items into
	int NumOfItems = ItemArray.Num();
	//RandomizedArray.SetNum(NumOfItems); //set the size of the new array equal to our current item array
	for (int i = 0; i < NumOfItems; i++) {

		//check if it's null? or maybe we still want to re-randomize if it's null and check that if it's placed

		int rand = FMath::RandRange(0, NumOfItems- i - 1);
		//LOG("ARRAY SPOT: %d, num of items: %d", rand, NumOfItems)
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

	// -- PLACE ITEMS --


	int NumOfSpawns = SpawnerArray.Num();
		//LOG("name: %s, NUM OF ITEMS %d", *GetName(), NumOfSpawns)
	for (int i = 0; i < NumOfSpawns; i++) {

		AActor* PlacedActor;



		if (IsValid(ItemArray[i])) {//if item array at i is not null, do nothing, otherwise empty items would cause a nullref
			if (IsValid(SpawnerArray[i])) {
				if (PlacedActor = GetWorld()->SpawnActor<AActor>(
					ItemArray[i], SpawnerArray[i]->GetActorLocation(),
					SpawnerArray[i]->GetActorRotation())) {

					PlacedActors.Add(PlacedActor);
					PlacedActor->SetOwner(this);

					//LOG("placed item number %d object name %s done by %s", i, *PlacedActor->GetName(), *GetName())

					//if we're spawning a powerup, set the reference to the spawn point
					//this is used for playing the collection audio
					if (ASpawnPowerup* PowerupSpawn = Cast<ASpawnPowerup>(SpawnerArray[i])) {
						if (UPowerupCollectibleBase* Powerup = PlacedActor->FindComponentByClass<UPowerupCollectibleBase>()) {
								Powerup->SpawnPoint = PowerupSpawn;
						}
					}
					//this is definitely improper inheritence, 
					// but I'm not sure how exactly to go about fixing it.
					// My best idea would be to have some setSpawnPoint() function that
					// I call on the "Powerup" Object, but since it's being originally 
					// passed as an Actor. I can't add or override any methods there.
					// at least not with more casting wonky-ness 

				}		
			}
			else {
				WARN("SPAWNER ARRAY NOT VALID FOR %s", *GetName())
			}

			//sets the spawn point for the collectionInteractable
			//could also theoretically do this in a separate powerupRandomizer class inherited from RandomizerBase
			//however this is currently the only different functionality. if I add more I'll refactor this as well
			
			//XRayCollectible, PowerupSpawnLocations[i]->GetActorLocation(), 
			//PowerupSpawnLocations[i]->GetActorRotation());

		}
	}
	ReceiveOnItemsPlaced();
	//LOG("ARRAY placed")
}


void ABWK_RandomizerBase::ResetItems()
{
	for (TObjectPtr<AActor> actor : PlacedActors) {
		if (actor) {

			if (ALevelPrefabBase* LevelPrefab = Cast<ALevelPrefabBase>(actor)) {
				//LOG("level prefab found")
				for (ABWK_RandomizerBase* randomizer : LevelPrefab->RandomizerArray ) {
					if (IsValid(randomizer)) {

						for (AActor* item : randomizer->PlacedActors) {
							if (IsValid(item)) {
									GetWorld()->DestroyActor(item);

							}
						}
					}
				}
			}

			//LOG("DESTROYED OBJECT  %s", *actor->GetName())
			GetWorld()->DestroyActor(actor);
		}
	}

	PlacedActors.Empty();

	RandomizeOrder();
	PlaceItems();
	//invoke placed items
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

