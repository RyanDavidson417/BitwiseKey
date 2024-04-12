// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelPrefabBase.generated.h"

class ABWK_RandomizerBase;

UCLASS()
class BITWISEKEY_API ALevelPrefabBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelPrefabBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Randomization")
	TArray<ABWK_RandomizerBase*> RandomizerArray;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
