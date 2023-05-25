// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "inClass/QuestSystem/Objectives/Objective.h"
#include "ObjReachDestination.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROG2_API UObjReachDestination : public UObjective
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UShapeComponent* Destination;

	virtual void ActivateObjective() override;
	virtual bool GetIsComplete() const override;

private:
	UFUNCTION()
	void ReachedDestination(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

private:
	//indicates if a destination has been reached
	UPROPERTY()
	bool bReachedDestination;
};
