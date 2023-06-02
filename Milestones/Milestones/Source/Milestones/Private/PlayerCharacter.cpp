// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Managers/BitwisePlayerController.h"
#include "Managers/BitwisePlayerState.h"
#include "Milestones/Milestones.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "BaseGizmos/GizmoElementShared.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimInstance.h"
#include "EnhancedInputSubsystems.h"
#include "CustomGameState.h"
#include "CustomGameMode.h"


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

	//PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	//PlayerMesh->SetOnlyOwnerSee(true);
	//PlayerMesh->SetupAttachment(FirstPersonCameraComponent);
	//PlayerMesh->bCastDynamicShadow = false; //these two lines were included in Unreal's stock code, but I'm inclined to leave them out
	//PlayerMesh->CastShadow = false
	//PlayerMesh->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));



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


	gm = GetWorld()->GetAuthGameMode<ACustomGameMode>();
	gs = Cast<ACustomGameState>(gm->GameState);

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TraceLine();

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	//UE_LOG(LogTemp, Warning, TEXT("running SetupPlayerComponent()"));
	//WARN("getting enhanced input component");
	//doncasting the PlayerInputComponent to be a UEnhancedInputComponent
	UEnhancedInputComponent* EIS = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	//bind the move action
	//WARN("Binding Move actions");
	//UE_LOG(LogTemp, Warning, TEXT("binding the move action"));
	EIS->BindAction(MovementAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	//bind the steer action
	EIS->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
	//bind the Interact action
	EIS->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter::Interact);
	//bind the invisActivate action;
	EIS->BindAction(InvisToggleAction, ETriggerEvent::Started, this, &APlayerCharacter::ToggleInvisibility);


	//bind the jump actions
	EIS->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EIS->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);


}

void APlayerCharacter::Move(const FInputActionInstance& Instance)
{

	lastMoveInput = Instance.GetValue().Get<FVector2D>();
	//UE_LOG(LogTemp, Warning, TEXT("MOVE INPUT detected"));

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

	//LOG("looking around");

	if (Controller != nullptr) 
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Interact(const FInputActionInstance& Instance)
{

	if (InteractionComponent != nullptr) {
		//UE_LOG(LogTemp, Warning, TEXT("You Collected the %s "), *InteractionComponent->Powerup);
		UE_LOG(LogTemp, Warning, TEXT("You Collected the "));
		InteractionComponent->Interact(Cast<APlayerController>(GetController()));

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("interaction called, interactable object DOESN'T exist"));

	}
}

void APlayerCharacter::TraceLine()
{

	//set up a line trace from our current position to a point interactionDistance ahead of us
	FVector EyesLoc;
	FRotator EyesRot;
	GetActorEyesViewPoint(EyesLoc, EyesRot);//maybe change this to be related to camera location
	FVector TraceStart = EyesLoc;
	//FVector TraceStart = GetActorLocation();

	//FVector TraceEnd = EyesLoc + EyesRot * interactionDistance;
	FVector TraceEnd = EyesLoc + GetActorForwardVector().RotateAngleAxis(  EyesRot.Pitch * -1, GetActorRightVector()) * interactionDistance;
		//GetActorForwardVector() * interactionDistance;

	//you can use FCollisionqueryParams to further configure the query
	FCollisionQueryParams QueryParams;
	//here we add outselves to the ingnored list so we won't block the trace
	QueryParams.AddIgnoredActor(this);

	//to run the query, you need a pointer to the current level, which you can get from an actor with GetWorld()
	// UWorld()->LineTraceSingleByChannel runs a line trace and returns the first actor hit over the provided collision channel.
	GetWorld()->LineTraceSingleByChannel(LineTraceHit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams);


	//you can use DrawDebug helpers and the log to help visualize and debug your trace queries
	
	//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, LineTraceHit.bBlockingHit ? FColor::Blue : FColor::Red, false, 0.0f, 0, 1.0f);
	//UE_LOG(LogTemp, Log, TEXT("Tracing line: %s to %s"), *TraceStart.ToCompactString(), *TraceEnd.ToCompactString());
	

	// If the trace hit something, bBlockingHit will be true,
// and its fields will be filled with detailed info about what was hit
	if (LineTraceHit.bBlockingHit && IsValid(LineTraceHit.GetActor()))
	{
		UActorComponent* InteractableObj = LineTraceHit.GetActor()->FindComponentByClass<UInteractionComponent>();

		//UE_LOG(LogTemp, Warning, TEXT("Trace hit actor: %s"), *LineTraceHit.GetActor()->GetName());// 
		if (IsValid(InteractableObj)){

			//UE_LOG(LogTemp, Warning, TEXT("INTERACTABLE Trace hit actor: %s"), *LineTraceHit.GetActor()->GetName());

			//MAYBE maybe set a bool to track whether we have one, and store a reference to the actor
			InteractionComponent = Cast<UCollectionInteractable>(InteractableObj);

		}
		else {
			InteractionComponent = nullptr;
		}
	}
	else {
		InteractionComponent = nullptr;
		//UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
	}

}

void APlayerCharacter::ToggleInvisibility(const FInputActionInstance& Instance)
{
	WARN("toggle invisibility input called");
	gm->ToggleInvisibility();
}
