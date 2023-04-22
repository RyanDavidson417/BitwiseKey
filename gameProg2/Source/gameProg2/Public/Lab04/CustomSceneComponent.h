// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Math/TransformNonVectorized.h"
#include "CustomSceneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPROG2_API UCustomSceneComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCustomSceneComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//setters for the localTransform variables
	void setLocalTransform(FTransform newTransform);
	void setLocalRotation(FQuat newRotation);
	void setLocalScale(FVector newScale);
	void setLocalTranslation(FVector newTranslation);
	
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(EditAnywhere)
	AActor* Parent;
	UPROPERTY(EditAnywhere)
	TArray<AActor *> Children;
	UPROPERTY(EditAnywhere)
	FTransform LocalTransform;
	
		
};
