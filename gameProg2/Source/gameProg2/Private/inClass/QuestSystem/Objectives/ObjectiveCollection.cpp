// Fill out your copyright notice in the Description page of Project Settings.


#include "inClass/QuestSystem/Objectives/ObjectiveCollection.h"

void UObjectiveCollection::ActivateObjective()
{
	Super::ActivateObjective();

	//if ordering is required
	if (bOrderRequired) {
		ActivateNextIncompleteObjective();

	}
	else {
		for (UObjective* Objective : ObjectiveList) {
			Objective->ActivateObjective();
		}
	}
}

bool UObjectiveCollection::GetIsComplete() const
{

	for (UObjective* Objective: ObjectiveList) {
		if (!Objective->GetIsComplete()) {
			//one of the objectives is incomplete, so not all are completed
			return false;
		}
	}
	//if we've made it here, then everything is complete
	return false;
}

void UObjectiveCollection::AddObjective(UObjective* ObjectiveToAdd)
{
	ObjectiveList.Add(ObjectiveToAdd);
}

TArray<UObjective*> UObjectiveCollection::GetSubObjectiveList()
{
	return ObjectiveList;
}

UObjective* UObjectiveCollection::FindNextIncompleteObjective()
{
	for (UObjective* Objective : ObjectiveList) {
		//if this objective is not complete
		if (!Objective->GetIsComplete()) {
			//one of the objectives is incomplete, so not all are completed
			return Objective;
		}
	}
	//there are no incomplete objectives, so we should complete the objective collection
	CompleteObjective();
	return nullptr;
}

void UObjectiveCollection::ActivateNextIncompleteObjective()
{

	//clear this objective's onCompleted Listeners - this design pattern is called "continuation passing style" - you're passing the computation that'll occur next . in web dev you're dealing with what happens when my function completes and what happens when I get an error
	OnCompleted.Clear();

	//find next incomplete objective
	UObjective* NextIncompleteObjective = FindNextIncompleteObjective();

	//make sure we actually got the objective pointer (in case everything is already completed)
	if(IsValid(NextIncompleteObjective)) {

		//activate the next incomplete objective
		NextIncompleteObjective->ActivateObjective();

		//delegate subscritption to activate the next objective when this one is completed. 
		NextIncompleteObjective->OnCompleted.AddDynamic(this, &UObjectiveCollection::ActivateNextIncompleteObjective);


	}

}


