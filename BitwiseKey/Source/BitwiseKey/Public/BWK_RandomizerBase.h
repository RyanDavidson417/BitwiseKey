// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "./Interactables/RandomItemSpawner.h"
#include "BWK_RandomizerBase.generated.h"

class AActorComponent;
class RandomItemSpawner;
class ABitwiseGameMode;
class ALevelPrefabBase;

UCLASS()
class BITWISEKEY_API ABWK_RandomizerBase : public AActor
{
	GENERATED_BODY()
	
// -- FUNCTIONS

public:	
	// Sets default values for this actor's properties
	ABWK_RandomizerBase();



	UFUNCTION()
	virtual void PlaceItems();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "OnItemsPlaced"))
	void ReceiveOnItemsPlaced(); //no c++ implementation
	virtual void ReceiveOnItemsPlaced_Implementation();
	virtual void RandomizeOrder();
	UFUNCTION()
	virtual void ResetItems();

	virtual void RemoveItemFromPlacedActors(TObjectPtr<AActor> actor);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// -- VARIABLES-- 

protected:

	TObjectPtr<ABitwiseGameMode> gm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Randomization")
	TArray<TSubclassOf<AActor>> ItemArray;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Randomization")
	TArray<ARandomItemSpawner*> SpawnerArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Randomization")
	TArray<TObjectPtr<AActor>> PlacedActors;


public:
	UPROPERTY(EditAnywhere, Category = "Randomization")
	TArray<TSubclassOf<AActor>> ItemArrayPlease;

};
