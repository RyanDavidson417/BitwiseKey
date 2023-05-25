// Fill out your copyright notice in the Description page of Project Settings.


#include "inClass/QuestSystem/Quests/Quest.h"
#include "inClass/QuestSystem/Objectives/ObjectiveCollection.h"

// Sets default values
AQuest::AQuest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AQuest::BeginPlay()
{
	Super::BeginPlay();

	//TODO: implement
	RootObjectiveCollection = SetupQuest();
	PopulateObjectives(RootObjectiveCollection);

	RootObjectiveCollection->ActivateObjective();


	
}

UObjectiveCollection* AQuest::SetupQuest()
{
	UE_LOG(LogTemp, Error, TEXT("Setup class called for base class"));
	return nullptr;
}

void AQuest::PopulateObjectives(UObjectiveCollection* RootObjCol)
{
	UE_LOG(LogTemp ,Error, TEXT("populate objectives called for base class"));

}

// Called every frame
void AQuest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UObjectiveCollection* AQuest::GetRootObjectiveCollection() const
{
	return RootObjectiveCollection;
}

