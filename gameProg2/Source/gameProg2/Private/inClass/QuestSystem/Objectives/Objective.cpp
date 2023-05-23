// Fill out your copyright notice in the Description page of Project Settings.


#include "inClass/QuestSystem/Objectives/Objective.h"

FText UObjective::GetObjectiveName() const
{
	return ObjectiveName;
}

void UObjective::SetObjectiveName(FText newName)
{
	ObjectiveName = newName;
}

bool UObjective::GetIsActive() const
{
	return bIsActive;
}

void UObjective::ActivateObjective()
{
	UE_LOG(LogTemp, Warning, TEXT("Objective activated: %s"), *ObjectiveName.ToString());

	//setactive state
	bIsActive = true;

}

bool UObjective::GetIsComplete() const
{

	return true;
}

void UObjective::CompleteObjective() const
{
	OnCompleted.Broadcast();
}
