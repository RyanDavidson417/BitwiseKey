// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Objective.generated.h"

//event that should broadcast when the objective is completed
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCompleted);
/**
 * 
 */
UCLASS(Abstract, Blueprintable)//abstract( no instance can exist within level, 
class GAMEPROG2_API UObjective : public UObject
{
	GENERATED_BODY()

protected:
		//denotes wheter the objective is currently in progress
		UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
		bool bIsActive;//

	//the name of the task associated with the objective
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
		FText ObjectiveName;

public:		
	UPROPERTY(BlueprintAssignable, Category = "ObjectiveEvents")
		FOnCompleted OnCompleted;

	//simple getter for the objective name
	UFUNCTION(Category = "Objective")
	FText GetObjectiveName() const;

	//simple setter for the objective name
	UFUNCTION(Category = "Objective")
	void SetObjectiveName(FText newName);


	//simple getter for the objective active state
	UFUNCTION(Category = "Objective")
		bool GetIsActive() const;

	//this is the function used to activate the objective
	UFUNCTION(Category = "Objective")
	virtual void ActivateObjective();

	//this is the function that is used to determine if the objective has been complete
	UFUNCTION(Category = "Objective")
	virtual bool GetIsComplete() const;



protected :
	//is called when the objective is complete
	void CompleteObjective() const;


};
