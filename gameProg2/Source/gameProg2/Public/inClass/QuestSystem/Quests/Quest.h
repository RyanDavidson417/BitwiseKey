// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quest.generated.h"

UCLASS()
class GAMEPROG2_API AQuest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//root (first/top level objective for the quest
	class UObjectiveCollection* RootObjectiveCollection;
	
	//constructs the root objective collection and associates objectives with the quest
	virtual UObjectiveCollection* SetupQuest();

	//populate the objectives and subObjectives of the RootObjectiveCollection
	virtual void PopulateObjectives();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//simple getter for rootObjectiveCollection
	virtual UObjectiveCollection* GetRootObjectiveCollection() const;

};
