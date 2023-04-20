// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Lab03SceneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPROG2_API ULab03SceneComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULab03SceneComponent();
	
	// Contains the default functionality (name is arbitrary)
	virtual void OnInteractedBehavior();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	float speed;
	
	UPROPERTY(EditAnywhere)
	float currRotation;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable Actor")
	void OnInteracted(); // The event itself
	void OnInteracted_Implementation(); //The default implementation of the behavior (required if BlueprintNativeEvent, optional if BlueprintImplementableEvent)
		
};
