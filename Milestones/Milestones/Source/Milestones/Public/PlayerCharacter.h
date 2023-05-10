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



	//references to the actions 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* LookAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		class UInputAction* JumpAction;

	//the base input mapping context we want to add
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputMappingContext* InputMapping;

	//first person camera
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FirstPersonCameraComponent;

	//max movement speed
	UPROPERTY(EditAnywhere)
		float MaxMoveSpeed;
	
	
	UPROPERTY(EditAnywhere)
		float interactionDistance;
		

	FVector2d lastLookInput;
	FVector2D lastMoveInput;

	FHitResult Hit;

	FVector TraceStart = GetActorLocation();

	FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * 1000.0f;



	//FCollisionQueryparams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_TRACE")), true, this);

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
