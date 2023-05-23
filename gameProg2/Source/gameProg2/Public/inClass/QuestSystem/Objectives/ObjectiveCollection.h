// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "inClass/QuestSystem/Objectives/Objective.h"
#include "ObjectiveCollection.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROG2_API UObjectiveCollection : public UObjective
{
	GENERATED_BODY()

		UPROPERTY()
		TArray<UObjective*> ObjectiveList;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))

		bool bOrderRequired;

	virtual void ActivateObjective() override;

	virtual bool GetIsComplete() const override;

	UFUNCTION(BlueprintCallable)
	virtual void AddObjective(UObjective* ObjectiveToAdd);

	UFUNCTION(BlueprintPure)
	TArray<UObjective*> GetSubObjectiveList();

private:
	//Helper function to identify the next objective in objective list that is incomplete
	UFUNCTION()
	UObjective* FindNextIncompleteObjective();

//helper function to activate the next objective in the objective list that is incomplete
	UFUNCTION()
	void ActivateNextIncompleteObjective();

};
