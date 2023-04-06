// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lab02Actor.generated.h"

UCLASS()
class GAMEPROG2_API ALab02Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALab02Actor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed;

	UPROPERTY(EditAnywhere)
	FVector EndPosition;

	UPROPERTY(VisibleAnywhere)
	FVector InitialPosition;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TheMesh;

	UPROPERTY(VisibleAnywhere)
	FVector Target; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
