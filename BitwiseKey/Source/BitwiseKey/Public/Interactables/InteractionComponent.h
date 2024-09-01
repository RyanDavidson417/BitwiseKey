// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"




UCLASS( ABSTRACT, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BITWISEKEY_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

	UPROPERTY(BlueprintReadWrite)
	bool bInteractable = true; 

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(APlayerController* playerController);

	virtual void Interact_Implementation(APlayerController* playerController);
		
};
