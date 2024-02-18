// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "BitwiseKey/BitwiseKey.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
//#include "BaseGizmos/GizmoElementShared.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimInstance.h"
#include "EnhancedInputSubsystems.h"
#include "BitwiseGameState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerStart.h" 
#include "BitwiseGameMode.h"


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

	gm = GetWorld()->GetAuthGameMode<ABitwiseGameMode>();
	gs = Cast<ABitwiseGameState>(gm->GameState);

	gm->D_OnReset.AddDynamic(this, &APlayerCharacter::ResetPlayer);

	setRandomStartRotation();

	characterMovement = GetCharacterMovement();


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
	EIS->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump); //would have to override if we wanted to start game timer on jump
	EIS->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

	EIS->BindAction(ResetPlayerAction, ETriggerEvent::Started, this, &APlayerCharacter::ResetFromPlayer);



}

void APlayerCharacter::Move(const FInputActionInstance& Instance)
{
	//used for game timer
	if (!bReceivedFirstPlayerInput) {
		gm->StartGameTimer();
		bReceivedFirstPlayerInput = true;
	}

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
	//used for game timer, could disable these lines if we wanted to be generous and only start the game timer when the player starts moving
	if (!bReceivedFirstPlayerInput) {
		gm->StartGameTimer();
		bReceivedFirstPlayerInput = true;
	}


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

	//used for game timer, probably not totally necessary to start it if the player hits the invisibility button, just for posterity
	if (!bReceivedFirstPlayerInput) {
		gm->StartGameTimer();
		bReceivedFirstPlayerInput = true;
	}

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
	//used for game timer, probably not totally necessary to start it if the player hits the invisibility button, just for posterity
	if (!bReceivedFirstPlayerInput) {
		gm->StartGameTimer();
		bReceivedFirstPlayerInput = true;
	}

	
	WARN("toggle invisibility input called");
	gm->ToggleInvisibility();

	if (gs->InvisibilityStruct.bIsActive) {

		GetCharacterMovement()->GravityScale = 1;
	}
	else {
		GetCharacterMovement()->GravityScale = 2;

	}

}

//void APlayerCharacter::DeactivateInvisibilityEffects()
//{
//
//}
//
//void APlayerCharacter::ActivateInvisibilityEffects()
//{
//	UCharacterMovementComponent* charMove = GetCharacterMovement();
//	if (gs->PowerupMap.Find(EPowerUpName::PE_Invisibility)->bIsActive) {
//		characterMovement->GravityScale = 1;
//		characterMovement->JumpZVelocity = 400;
//		characterMovement->MaxWalkSpeed = 1100;
//	}
//	else {
//		characterMovement->GravityScale = 2;
//		characterMovement->JumpZVelocity = 500;
//		characterMovement->MaxWalkSpeed = 700;
//
//	}
//}

void APlayerCharacter::ActivateStaminaEffects()
{
	//zzzz
	//step though each powerup. check if it's a stamina related ability, and if so deactivate it
	//we might need to refactor it from being a map

	if (gs->XRayStruct.bIsStaminaAbility) {
		//no implementation needed as xray (currently) doesn't have any player vals associated
		//theoretically this statement won't even ever activate
	}

	if (gs->InvisibilityStruct.bIsStaminaAbility) {
		//no implementation needed as invisibility (currently) doesn't have any player vals associated
		//theoretically this statement won't even ever activate
	}

	if (gs->SpeedBoostStruct.bIsStaminaAbility) {
		characterMovement->MaxWalkSpeed = gs->SpeedBoostStruct.ActiveValue;
	}

	if (gs->JumpBoostStruct.bIsStaminaAbility) {
		characterMovement->JumpZVelocity = gs->JumpBoostStruct.ActiveValue;
	}
}

void APlayerCharacter::DeactivateStaminaEffects()
{

	if (gs->XRayStruct.bIsStaminaAbility) {
		//no implementation needed as xray (currently) doesn't have any player vals associated
		//theoretically this statement won't even ever activate
	}

	if (gs->InvisibilityStruct.bIsStaminaAbility) {
		//no implementation needed as invisibility (currently) doesn't have any player vals associated
		//theoretically this statement won't even ever activate
	}

	if (gs->SpeedBoostStruct.bIsStaminaAbility) {
		characterMovement->MaxWalkSpeed = gs->SpeedBoostStruct.defaultValue;
	}

	if (gs->JumpBoostStruct.bIsStaminaAbility) {
		characterMovement->JumpZVelocity = gs->JumpBoostStruct.defaultValue;
	}
}

void APlayerCharacter::ResetPlayer()
{
	SetActorLocation(gm->FindPlayerStart(Controller)->GetActorLocation());
	
	bReceivedFirstPlayerInput = false;

	DeactivateStaminaEffects();


	setRandomStartRotation();

}


void APlayerCharacter::setRandomStartRotation()
{
	int randDirection = FMath::RandRange(0, 3); //0 is forward, 1 is right, etc.

	if (Controller != nullptr)
	{
		Controller->SetControlRotation(FRotator::ZeroRotator);
	}
	AddControllerYawInput((randDirection * 90) / 2.5);

	//LOG("random number: %d, direction: %d", randDirection, randDirection * 90);

}

void APlayerCharacter::ResetFromPlayer()
{
	WARN("reset action called from player")
		gm->D_OnReset.Broadcast();
}
