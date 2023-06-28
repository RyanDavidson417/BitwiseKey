// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FakeWall.generated.h"

class ACustomGameMode;
class ACustomGameState;

UCLASS()
class MILESTONES_API AFakeWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFakeWall();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	TObjectPtr<ACustomGameMode> gm;
	TObjectPtr<ACustomGameState> gs;
};
