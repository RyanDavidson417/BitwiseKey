// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;


UCLASS()
class MILESTONES_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()


	 


public:
	// Sets default values for this character's properties
	APlayerCharacter();


	//static mesh
	UPROPERTY(VisibleDefaultsOnly, Category = mesh)
		USkeletalMeshComponent* PlayerMesh;

	//references to the actions 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputAction* SteeringAction;

	//the base input mapping context we want to add
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputMappingContext* InputMapping;

	//first person camera
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FirstPersonCameraComponent;

	//max movement speed
	UPROPERTY(EditAnywhere)
		float MaxMoveSpeed;

	FVector2d lastLookInput;
	FVector2D lastMoveInput;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//update movement and looking
	virtual void Move(const struct FInputActionInstance& Instance);
	virtual void Look(const FInputActionInstance& InputActionInstance);

	//reference to camera component
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};
