// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomItemSpawner.generated.h"


class ACustomGameMode;
class ACustomGameState;

UCLASS()
class BITWISEKEY_API ARandomItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARandomItemSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Spawn(TSubclassOf<AActor*> actor);


public:
	//used to reference the randomized array in the gamestate, on generation we reference the nth index to determine which ability we spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectibles")
	int spawnOrder;

protected:

	TObjectPtr<ACustomGameMode> gm;
	TObjectPtr<ACustomGameState> gs;

};
