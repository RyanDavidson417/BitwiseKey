// Fill out your copyright notice in the Description page of Project Settings.


#include "inClass/QuestSystem/Quests/Quest.h"

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
	
}

UObjectiveCollection* AQuest::SetupQuest()
{
	UE_LOG(LogTemp, Error, TEXT("Setup class called for base class"));
	return nullptr;
}

void AQuest::PopulateObjectives()
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

