// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Lab06MovementPawn.generated.h"

class UCameraComponent;

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

	//first person camera
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;
	
	//max movement speed
	UPROPERTY(EditAnywhere)
	float MaxMoveSpeed;

		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	FVector2d lastSteerInput;
	bool lastMoveInput;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//define a move function
	virtual void Move(const struct FInputActionInstance& Instance);
	virtual void Steer(const FInputActionInstance& InputActionInstance);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UCameraComponent* GetFirstPersonCameraComponent() const {return FirstPersonCameraComponent; }

};
