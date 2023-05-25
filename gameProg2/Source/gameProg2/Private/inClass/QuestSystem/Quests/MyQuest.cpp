// Fill out your copyright notice in the Description page of Project Settings.


#include "inClass/QuestSystem/Quests/MyQuest.h"
#include "inClass/QuestSystem/Objectives/ObjectiveCollection.h"
#include "inClass/QuestSystem/Objectives/ObjReachDestination.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

AMyQuest::AMyQuest()
{
	//create first destination trigger box and initialize its parameters
	FirstDestinationTriggerBox = CreateDefaultSubobject<UBoxComponent>("FirstDestinationTriggerBox");
	FirstDestinationTriggerBox->SetupAttachment(RootComponent);
	FirstDestinationTriggerBox->InitBoxExtent(FVector(100, 100, 100));
	FirstDestinationTriggerBox->SetGenerateOverlapEvents(true);
	FirstDestinationTriggerBox->SetCollisionProfileName(TEXT("Trigger"), false);

	//create first destination trigger box and initialize its parameters
	SecondDestinationTriggerSphere = CreateDefaultSubobject<USphereComponent>("SecondDestinationTriggerBox");
	SecondDestinationTriggerSphere->SetupAttachment(RootComponent);
	SecondDestinationTriggerSphere->InitSphereRadius(50);
	SecondDestinationTriggerSphere->SetGenerateOverlapEvents(true);
	SecondDestinationTriggerSphere->SetCollisionProfileName(TEXT("Trigger"), false);





}

UObjectiveCollection* AMyQuest::SetupQuest()
{

	UObjectiveCollection* RootObjColl = NewObject<UObjectiveCollection>(this, 
		UObjectiveCollection::StaticClass(), TEXT("Root Objective Collection"));
	
	RootObjColl->bOrderRequired = true;
	RootObjColl->SetObjectiveName(FText::FromString("A long way home"));

	return RootObjColl;
}

void AMyQuest::PopulateObjectives(UObjectiveCollection* RootObjCollection)
{
	UObjReachDestination* ReachFirstDestinationObjective = NewObject<UObjReachDestination>(this,
		UObjReachDestination::StaticClass(), TEXT("Reach First destination Objective"));

	ReachFirstDestinationObjective->SetObjectiveName(FText::FromString("reach town A"));
	ReachFirstDestinationObjective->Destination = FirstDestinationTriggerBox; 
	//add the objective to the root objective collection
	RootObjectiveCollection->AddObjective(ReachFirstDestinationObjective);

	
	UObjReachDestination* ReachSecondDestinationObjective = NewObject<UObjReachDestination>(this,
		UObjReachDestination::StaticClass(), TEXT("Reach Second destination Objective"));

	ReachSecondDestinationObjective->SetObjectiveName(FText::FromString("reach town A"));
	ReachSecondDestinationObjective->Destination = SecondDestinationTriggerSphere;
	//add the objective to the root objective collection
	RootObjectiveCollection->AddObjective(ReachSecondDestinationObjective);

}
