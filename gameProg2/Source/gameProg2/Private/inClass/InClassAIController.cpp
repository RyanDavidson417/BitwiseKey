// Fill out your copyright notice in the Description page of Project Settings.


#include "inClass/InClassAIController.h"


AInClassAIController:: AInClassAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	MoveSpeed = 100;
}

void AInClassAIController::BeginPlay()
{
	Super::BeginPlay();

	if(GetPawn() == nullptr)
	{
		//WARN("simple ai controller not possesing anything
	}
	
}

void AInClassAIController::Tick(float DeltaSeconds)
{

	Super::Tick(DeltaSeconds);

	TObjectPtr<APawn> pawn = GetPawn<APawn>();
	if(pawn != nullptr)
	{
		pawn->AddMovementInput(pawn->GetActorForwardVector() * MoveSpeed *DeltaSeconds);
		
	} else
	{
			//WARN("NOT CONNECTED TO A PARENT")
	}
}
