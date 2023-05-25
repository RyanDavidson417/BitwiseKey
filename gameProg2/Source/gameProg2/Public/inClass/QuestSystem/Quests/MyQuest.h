// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "inClass/QuestSystem/Quests/Quest.h"
#include "MyQuest.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROG2_API AMyQuest : public AQuest
{
	GENERATED_BODY()

public:
	AMyQuest();

private:
	//the trigger that fires the destination reached events
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
	class UBoxComponent* FirstDestinationTriggerBox;

	//the trigger that fires the destination reached events
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
		class USphereComponent* SecondDestinationTriggerSphere;

protected:
	virtual UObjectiveCollection* SetupQuest() override;
	virtual void PopulateObjectives(UObjectiveCollection* RootObjCollection) override;

	
};
