// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "InClassAIController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROG2_API AInClassAIController : public AAIController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;
	AInClassAIController();

	virtual void BeginPlay() override;
	virtual void Tick(float DelaSeconds) override;
	
};
