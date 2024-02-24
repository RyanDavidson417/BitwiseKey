// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactables/XRayVision.h"  
#include "BitwiseGameMode.h"
#include "Interactables/RandomItemSpawner.h"
#include "ASpawnPowerup.generated.h"

class ABitwiseGameMode;
class UAudioComponent;
class ABitwiseGameState;
class UXRayVision;
class ARandomItemSpawner;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BITWISEKEY_API ASpawnPowerup : public ARandomItemSpawner
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPowerup();

	UPROPERTY(EditAnywhere, blueprintReadWrite, Category = Audio)
		TObjectPtr<class UAudioComponent> CollectionSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Spawn(TSubclassOf<AActor*> actor) override;
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	//used to reference the randomized array in the gamestate, on generation we reference the nth index to determine which ability we spawn
	

protected:

	TObjectPtr<ABitwiseGameMode> gm;
	TObjectPtr<ABitwiseGameState> gs;
};
