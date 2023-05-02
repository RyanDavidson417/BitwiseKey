// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Lab06MovementPawn.generated.h"

UCLASS()
class GAMEPROG2_API ALab06MovementPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALab06MovementPawn();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
//	TObjectPtr<class UStaticMeshComponent> StaticMesh;
	
	//references to the actions 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* MovementAction; 
//	TObjectPtr<class UInputAction> MovementAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SteeringAction;
//	TObjectPtr<class UInputAction> SteeringAction;

	//the base input mapping context we want to add
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* InputMapping;
//	TSoftObjectPtr<class UInputMappingContext> InputMapping;

	//max movement speed
	UPROPERTY(EditAnywhere)
	float MaxMoveSpeed;

	//define a move function
	virtual void Move(const struct FInputActionInstance& Instance);
		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	FVector2d lastSteerInput;
	bool lastMoveInput;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
