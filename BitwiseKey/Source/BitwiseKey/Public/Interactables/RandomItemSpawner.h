// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomItemSpawner.generated.h"


struct FLinearColor;
class ABitwiseGameMode;
class ABitwiseGameState;
class UPowerupCollectibleBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPowUpAssignedNPSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPowUpAssignedSignature, FLinearColor, PowerupColor);

UCLASS()
class BITWISEKEY_API ARandomItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Spawn(TSubclassOf<AActor*> actor);

	// Sets default values for this actor's properties
	ARandomItemSpawner();

	//sort of a late OnReset delegate, called every on reset after the powerups have been assigned
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnPowUpAssignedSignature D_OnPowUpAssignedNPDelegate;

	//sort of a late OnReset delegate, called every on reset after the powerups have been assigned
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnPowUpAssignedSignature D_OnPowUpAssignedDelegate;
	
	UPROPERTY(BlueprintReadOnly)
	UPowerupCollectibleBase* CurrentPowerup;


public:
	//used to reference the randomized array in the gamestate, on generation we reference the nth index to determine which ability we spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectibles")
	int spawnOrder;

protected:

	TObjectPtr<ABitwiseGameMode> gm;
	TObjectPtr<ABitwiseGameState> gs;

};
