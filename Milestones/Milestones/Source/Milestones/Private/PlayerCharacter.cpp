// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "BaseGizmos/GizmoElementShared.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimInstance.h"
#include "EnhancedInputSubsystems.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	PlayerMesh->SetOnlyOwnerSee(true);
	PlayerMesh->SetupAttachment(FirstPersonCameraComponent);
	//PlayerMesh->bCastDynamicShadow = false; //these two lines were included in Unreal's stock code, but I'm inclined to leave them out
	//PlayerMesh->CastShadow = false
	PlayerMesh->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));



}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//add input mapping context
	if (APlayerController* playerController = Cast<APlayerController>(GetController()))
	{

		//UE_LOG(LogTemp, Warning, TEXT("checking to see if there's a local player"));
		if (ULocalPlayer* localPlayer = Cast<ULocalPlayer>(playerController->GetLocalPlayer()))
		{
			//UE_LOG(LogTemp, Warning, TEXT("looking for input system "));
			if (UEnhancedInputLocalPlayerSubsystem* inputSystem =
				localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				//UE_LOG(LogTemp, Warning, TEXT("loading inputMapping"));
				if (InputMapping != nullptr)
				{

					//UE_LOG(LogTemp, Warning, TEXT("reached end of playerController nested ifs"));
					//UE_LOG(LogTemp, Warning, TEXT("adding mapping context"));
					inputSystem->AddMappingContext(InputMapping, 0);
				}
			}
		}
	}
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	UE_LOG(LogTemp, Warning, TEXT("running SetupPlayerComponent()"));
	//WARN("getting enhanced input component");
	//doncasting the PlayerInputComponent to be a UEnhancedInputComponent
	UEnhancedInputComponent* EIS = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	//bind the move action
	//WARN("Binding Move actions");
	UE_LOG(LogTemp, Warning, TEXT("binding the move action"));
	EIS->BindAction(MovementAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	//bind the steer action
	EIS->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

}

void APlayerCharacter::Move(const FInputActionInstance& Instance)
{

	lastMoveInput = Instance.GetValue().Get<FVector2D>();
	//LOG("MOVE INPUT: (%f, %f)", lastSteerInput.X, lastSteerInput.Y);
	UE_LOG(LogTemp, Warning, TEXT("MOVE INPUT detected"));

	//FVector2D MovementVector = Value.Get<FVector2D>()

	if (Controller != nullptr)
	{

		AddMovementInput(GetActorForwardVector(), lastMoveInput.Y);
		AddMovementInput(GetActorRightVector(), lastMoveInput.X);

	}
}


void APlayerCharacter::Look(const FInputActionInstance& InputActionInstance)
{

	FVector2D LookAxisVector = InputActionInstance.GetValue().Get<FVector2D>();

	if (Controller != nullptr) 
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

