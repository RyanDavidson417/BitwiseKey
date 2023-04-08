// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InClassLab03.generated.h"

UCLASS()
class GAMEPROG2_API AInClassLab03 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInClassLab03();

	// UPROPERTY(EditAnywhere)
	// float fooBar;

	// UPROPERTY(VisibleAnywhere)
	// TObjectPtr<class InClass03ActorComponent> InClass03Compoment;
	//
	// UPROPERTY(VisibleAnywhere)
	// TObjectPtr<class InClass03ActorComponent> Dynamic03Compoment;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
