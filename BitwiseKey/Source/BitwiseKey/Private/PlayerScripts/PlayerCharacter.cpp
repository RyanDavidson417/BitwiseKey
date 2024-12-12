// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerScripts/PlayerCharacter.h"
#include "BitwiseKey/BitwiseKey.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "BaseGizmos/GizmoElementShared.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h" 
#include "Animation/AnimInstance.h"
#include "Core/OptionsSaveGame.h"
#include "Core/BWK_UserWidget.h"
#include "EnhancedInputLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "Core/BitwiseGameState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerStart.h" 
#include "PlayerScripts/BitwisePlayerState.h"
#include "LevelObjects/PowerupDataBase.h"
#include "CommonInputSubsystem.h"
#include "Core/BitwiseGameMode.h"


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



	InvisHumAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("InvisHumComponent"));

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
	ps = Cast<ABitwisePlayerState>(GetPlayerState());


	gm->D_OnReset.AddDynamic(this, &APlayerCharacter::ResetPlayer);

	setRandomStartRotation();

	CharacterMovement = GetCharacterMovement();

	DefaultAirControl = CharacterMovement->AirControl;

	//if (OptionsSaveGame = Cast<UOptionsSaveGame>(UGameplayStatics::LoadGameFromSlot("SaveGame", 0))) {
	//	UpdateLookControls(OptionsSaveGame);
	//} else {
	//	WARN("cast to OptionsSaveGame failed. no save game loaded")
	//}



	LOG("delegate ping")
	//UOptionsSaveGame BPSaveGame = 
	//TScriptInterface<UOptionsSaveGame> BPSaveGame = 

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


	gm = GetWorld()->GetAuthGameMode<ABitwiseGameMode>();
	gs = Cast<ABitwiseGameState>(gm->GameState);

	Super::SetupPlayerInputComponent(PlayerInputComponent);


	//UE_LOG(LogTemp, Warning, TEXT("running SetupPlayerComponent()"));
	//WARN("getting enhanced input component");
	//doncasting the PlayerInputComponent to be a UEnhancedInputComponent
	UEnhancedInputComponent* EIS = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	//bind the move action
	//WARN("Binding Move actions");
	//UE_LOG(LogTemp, Warning, TEXT("binding the move action"));
	EIS->BindAction(MovementAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	EIS->BindAction(MovementAction, ETriggerEvent::Started, this, &APlayerCharacter::DismissSplashScreen);
	EIS->BindAction(MovementAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopMoving);
	//bind the steer action
	EIS->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
	//bind the Interact action
	EIS->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter::Interact);
	//bind the invisActivate action;
	EIS->BindAction(InvisToggleAction, ETriggerEvent::Started, this, &APlayerCharacter::ToggleInvisibility);
	EIS->BindAction(InvisToggleAction, ETriggerEvent::Completed, this, &APlayerCharacter::ReleaseInvisibility);


	//bind the jump actions
	EIS->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump); //would have to override if we wanted to start game timer on jump
	EIS->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

	EIS->BindAction(ResetPlayerAction, ETriggerEvent::Started, this, &APlayerCharacter::ResetFromPlayer);

	EIS->BindAction(ActivateSpeedAction, ETriggerEvent::Started, this, &APlayerCharacter::ToggleStamina);
	EIS->BindAction(ActivateSpeedAction, ETriggerEvent::Completed, this, &APlayerCharacter::ReleaseStamina);
	
	if (UGameplayStatics::DoesSaveGameExist(gs->OptionsSlotName, 0)) {
		UOptionsSaveGame* sg = Cast<UOptionsSaveGame>(UGameplayStatics::LoadGameFromSlot(gs->OptionsSlotName, 0));
		LOG("save game found")
		if (sg->ToggleSprint) {
					
			//InvisToggleAction->bConsumeInput = true;
		}
		else {
			//InvisToggleAction->bConsumeInput = false;
		}
	}
	else {
		//save game not found, default to toggle
		LOG("save game not found")
		InvisToggleAction->bConsumeInput = true;
	}


}

void APlayerCharacter::DismissSplashScreen(const FInputActionInstance& Instance) {

	LOG("dismiss")

	//if we have a current widget and it's a splash screen
	if (IsValid(CurrentWidget) && CurrentWidget->bIsSplashScreen) {

		//the following lines are just some complicated retrieval and casting to make sure we're using MKB
		//so that we only dismiss when the player hits a key, rather than pushing the joystick
		if (const APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
		{
			if (const ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
			{
				if (const UCommonInputSubsystem* CommonInputSubsystem = LocalPlayer->GetSubsystem<UCommonInputSubsystem>())
				{
					if (const ECommonInputType InputType = CommonInputSubsystem->GetCurrentInputType(); InputType == ECommonInputType::MouseAndKeyboard)
					{
						CurrentWidget->HideMenu();
						
					}

				}
			}
		}
	}

}



void APlayerCharacter::Move(const FInputActionInstance& Instance)
{


	if (IsValid(gm) && gm->bGameTimerRunning) {

		//if (IsValid(CurrentWidget)) {
		//	LOG(
		// ")
		//		CurrentWidget->HideMenu();
		//}

		if (!gm->IsPaused()) {
		}

		if (bIsMoving) {//provided we're not already moving
			if (!bStaminaActive) {
				PlayMovementSound(0);
			}
			else {
				PlayMovementSound(1);
			}
		}

		bIsMoving = true;
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

			if (!bStaminaActive) { //if we're just walking
				PlayMovementSound(0);
			
			
				if (IsValid(WalkingAudio)) {
					//// if the movement audio component is valid, it's already playing
					//if (!IsValid(CurrentMovementAudioComponent)) {
					//	CurrentMovementAudioComponent = UGameplayStatics::CreateSound2D(this, WalkingAudio);
					//	CurrentMovementAudioComponent->Play();

					//	//do we want the sprint end audio to play as a transition to walking?
					//	//can we?
					//	//zzz
					//}
					//else {
					//	//LOG("already playing walki8ng sound")
					//}
				}
			}
			else {//if we're sprinting
				PlayMovementSound(1);


			}

			AddMovementInput(GetActorForwardVector(), lastMoveInput.Y);
			AddMovementInput(GetActorRightVector(), lastMoveInput.X);
		}	
	}
}

void APlayerCharacter::StopMoving(const FInputActionInstance& Instance)
{
	if (bStaminaActive) {
		if (IsValid(gm)) {
			gm->DeactivateStamina();
		}
	}

	bIsMoving = false;

	StopMovementSound();

	if (bStaminaActive) {
		//throws exception access violation 
		if (IsValid(SprintEndAudio)) {
			//UGameplayStatics::PlaySound2D(this, );
			PlayAbilitySound(SprintEndAudio);

		}
	}
}


void APlayerCharacter::Look(const FInputActionInstance& InputActionInstance)
{
	if (IsValid(gm) && gm->bGameTimerRunning) {
		FVector2D LookAxisVector = InputActionInstance.GetValue().Get<FVector2D>();

		//LOG("looking around");

		if (IsValid(gs)) {
			if (ps->bInvertXAxis) {
				LookAxisVector.X = LookAxisVector.X * -1;
				LOG("inverting x")
			}
			if (ps->bInvertYAxis) {
				LOG("inverting y")
				LookAxisVector.Y = LookAxisVector.Y * -1;
			}

			LookAxisVector.X = LookAxisVector.X * ps->fXSensitivity;
			LookAxisVector.Y = LookAxisVector.Y * ps->fYSensitivity;

			//zzz
			//check whether the savegame is set and if so invert the value
		}
		else {
			WARN("save game invalid")
		}

		if (Controller != nullptr)
		{
			AddControllerYawInput(LookAxisVector.X);
			AddControllerPitchInput(LookAxisVector.Y);
		}
	}
	
}

void APlayerCharacter::Jump()
{
	
	LOG("dismiss jump")
	if (IsValid(CurrentWidget) && CurrentWidget->bIsSplashScreen) {
		LOG("dismiss jump")
		CurrentWidget->HideMenu();
	}
	else {
		LOG("didn't dismiss, because: ")
			if (!IsValid(CurrentWidget)) {
						LOG("it wasn't valid")
			}
			else if(CurrentWidget->bIsSplashScreen){
				LOG("it's not a splash screen")
			} else {
				LOG("idk why actually")
			}
	}

	if (!gm->IsPaused()) {
		if (IsValid(gm) && gm->bGameTimerRunning) {
			if (JumpCurrentCountPreJump == 0) {//if this is our first jump
				//play first jump sound
				if (IsValid(FirstJumpSound)) {
					//UGameplayStatics::PlaySound2D(this, FirstJumpSound);
					PlayAbilitySound(FirstJumpSound);

				}
			}
			else if (gs->JumpBoostData->bCollected && JumpCurrentCountPreJump == JumpMaxCount - 1) {
				//play second jump sound
				if (IsValid(DoubleJumpSound)) {
					//UGameplayStatics::PlaySound2D(this, );		
					PlayAbilitySound(DoubleJumpSound);


				}
			}
			Super::Jump();
		}
	}

}

void APlayerCharacter::Interact(const FInputActionInstance& Instance)
{

	if (IsValid(CurrentWidget) && CurrentWidget->bIsSplashScreen) {
		LOG("HIDING")
			CurrentWidget->HideMenu();
	}

	if (!gm->IsPaused()) {
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
		UInteractionComponent* InteractableObj = LineTraceHit.GetActor()->FindComponentByClass<UInteractionComponent>();
		InteractionComponent = LineTraceHit.GetActor()->FindComponentByClass<UInteractionComponent>();

		//UE_LOG(LogTemp, Warning, TEXT("Trace hit actor: %s"), *LineTraceHit.GetActor()->GetName());// 
		if (IsValid(InteractionComponent)){

			if (!InteractionComponent->bInteractable) {
				InteractionComponent = nullptr;
			}
			//UE_LOG(LogTemp, Warning, TEXT("INTERACTABLE Trace hit actor: %s"), *LineTraceHit.GetActor()->GetName());

			//MAYBE maybe set a bool to track whether we have one, and store a reference to the actor
			//InteractionComponent = InteractableObj;

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


	if (IsValid(CurrentWidget) && CurrentWidget->bIsSplashScreen) {
		LOG("HIDING")
			CurrentWidget->HideMenu();
	}

	if (!gm->IsPaused()) {
		if (!gs->InvisibilityData->ActiveValue //if we're NOT already invisible
			 || gs->InvisibilityData->ActiveValue && ps->bToggleInvis) { //or we are invisible, and we're using toggle
			//Instance.GetTriggerEvent() == FInputActionInstance.
			if (IsValid(gm)) {
				gm->ToggleInvisibility();
			}

		}
	}

}

void APlayerCharacter::ReleaseInvisibility(const FInputActionInstance& Instance)
{


	if (IsValid(CurrentWidget) && CurrentWidget->bIsSplashScreen) {
		LOG("HIDING")
			CurrentWidget->HideMenu();
	}

	if (!gm->IsPaused()) {
		if (gs->InvisibilityData->bEnabled && !ps->bToggleInvis) {
			if (IsValid(gm)) {
				gm->ToggleInvisibility();
			}
		}
	}

}

void APlayerCharacter::ToggleStamina(const FInputActionInstance& Instance)
{

	if (IsValid(CurrentWidget) && CurrentWidget->bIsSplashScreen) {
		LOG("HIDING")
			CurrentWidget->HideMenu();
	}

	if (!gm->IsPaused()) {
		if (!gs->SpeedBoostData->bEnabled  /*if we're not sprinting*/
			|| (gs->SpeedBoostData->bEnabled && ps->bToggleSprint)) { //or if we are sprinting, and it's a toggle
			if (IsValid(gm)) {
				LOG("starting sprint")
				gm->ToggleStamina();
			}
			else {
				ERROR("ERROR: playercharacter.cpp reference to gamemode NOT VALID")
			}
		}
		else {
			LOG("false")
		}
	}

}

void APlayerCharacter::ReleaseStamina(const FInputActionInstance& Instance)
{

	if (IsValid(CurrentWidget) && CurrentWidget->bIsSplashScreen) {
		LOG("HIDING")
			CurrentWidget->HideMenu();
	}

	if (!gm->IsPaused()) {
		if (gs->SpeedBoostData->bEnabled && !ps->bToggleSprint) {
			if (IsValid(gm)) {
				gm->ToggleStamina();
			}
			else {
				ERROR("ERROR: playercharacter.cpp reference to gamemode NOT VALID")
			}
		}
	}

}

void APlayerCharacter::ActivateStaminaEffects()
{


	StopMovementSound();
	FOnFOVIncreaseDelegate.Broadcast(SprintingFOV);

	if (IsValid(SprintStartAudio)) {
		//UGameplayStatics::PlaySound2D(this, );

		PlayAbilitySound(SprintStartAudio);
	}
	else {
		LOG("NOT VALID")
	}

	bStaminaActive = true;

	CharacterMovement->MaxWalkSpeed = gs->SpeedBoostData->ActiveValue;
	CharacterMovement->AirControl = 1;
}


void APlayerCharacter::DeactivateStaminaEffects_Implementation(bool bRanFullyOut)
{
	LOG("c++ ")
	FOnFOVDecreaseDelegate.Broadcast(DefaultFOV);
	
	//play sprint end sounds
	if (bIsMoving && bStaminaActive) {

		StopMovementSound();
		if (bIsMoving) { //if we're still moving we're walking
			PlayMovementSound(0); //so play walk audio
		}

		if (IsValid(SprintEndAudio)) {
			//UGameplayStatics::PlaySound2D(this, );
			PlayAbilitySound(SprintEndAudio);

		}
		else {
			WARN("sprint end audio not valid")
		}

		if (bRanFullyOut) {
			if (IsValid(gs)) {
				if (gs->gameTimer > .1f) {
					if (IsValid(StaminaOutAudio)) {
						//UGameplayStatics::PlaySound2D(this, );
						PlayAbilitySound(StaminaOutAudio);

					}
				}
				else {
					LOG("timer: %d", gs->gameTimer)
				}
			}
			else {
				ERROR("GAMEMODE REF NOT VALID")
			}
		}
	}

	bStaminaActive = false;

	CharacterMovement->MaxWalkSpeed = gs->SpeedBoostData->defaultValue;
	CharacterMovement->AirControl = DefaultAirControl;


}

void APlayerCharacter::PlayAbilitySound(USoundBase* sound){

	if (IsValid(CurrentAbilitySound) && CurrentAbilitySound->IsPlaying()) {
		CurrentAbilitySound->SetActive(false);
		CurrentAbilitySound = nullptr;
	}
	CurrentAbilitySound = UGameplayStatics::SpawnSound2D(this, sound);

}

void APlayerCharacter::PauseAbilitySound() {
	if (IsValid(CurrentAbilitySound)) {
		LOG("should be pausing sound")
			CurrentAbilitySound->SetActive(false);
	}
}

void APlayerCharacter::UnPauseAbilitySound() {
	LOG("should be playing sound")

}



void APlayerCharacter::ActivateJumpBoost()
{
	CharacterMovement->JumpZVelocity = gs->JumpBoostData->ActiveValue;
}

void APlayerCharacter::DeactivateJumpBoost()
{
	CharacterMovement->JumpZVelocity = gs->JumpBoostData->defaultValue;
}

void APlayerCharacter::ResetPlayer()
{
	SetActorLocation(gm->FindPlayerStart(Controller)->GetActorLocation());
	
	bReceivedFirstPlayerInput = false;

	JumpMaxCount = gs->DoubleJumpData->defaultValue;
	DeactivateJumpBoost();
	DeactivateStaminaEffects();
	setRandomStartRotation();

	CharacterMovement->Velocity -= CharacterMovement->Velocity;
	
	if (IsValid(CurrentWidget)) {

		CurrentWidget->HideMenu();
	}


}


void APlayerCharacter::setRandomStartRotation()
{
	int randDirection = FMath::RandRange(0, 3); //0 is forward, 1 is right, etc.

	if (Controller != nullptr)
	{
		Controller->SetControlRotation(FRotator::ZeroRotator);
	}
	RandomStartingRotation = FRotator(0, (randDirection * 90) / 2.5, 0);
	AddControllerYawInput((randDirection * 90) / 2.5);

	//LOG("random number: %d, direction: %d", randDirection, randDirection * 90);

}

void APlayerCharacter::ResetFromPlayer()
{

	UGameplayStatics::SetGamePaused(this, false);
	WARN("reset action called from player")
		gm->D_OnReset.Broadcast();
}

void APlayerCharacter::UpdateToggles()
{
	LOG("yeah it happens")
	//UEnhancedInputComponent* EIS = CastChecked<UEnhancedInputComponent>(GetController()->InputComponent);

	//LOG("updating toggles: it %S a toggle", ps->bToggleSprint ? TEXT("as") : TEXT("bisn't"))
	//ActivateSpeedAction->bConsumeInput = ps->bToggleSprint;
	////UInputTriggerReleased ended;
	//
	//if (ps->bToggleSprint) { //if we want to operate by toggle

	//	for (UInputTrigger* Trigger : ActivateSpeedAction->Triggers) {
	//		if (UInputTriggerReleased* ReleaseTriggerR = Cast<UInputTriggerReleased>(Trigger)) { //if a release trigger is in the array
	//			ActivateSpeedAction->Triggers.Remove(ReleaseTriggerR);
	//		}
	//	}
	//}
	//else { //if by hold
	//	
	//	UInputTriggerReleased* ReleaseTriggerA = NewObject<UInputTriggerReleased>();
	//	
	//	bool bReleaseExists = false;
	//	for (UInputTrigger* Trigger : ActivateSpeedAction->Triggers) {
	//		if(UInputTriggerReleased* ReleaseTrigger = Cast<UInputTriggerReleased>(Trigger)) { //if a release trigger is in the array
	//			UE_LOG(LogTemp, Error, TEXT("ERROR: adding release trigger to ActivateSpeed action, but release trigger already exists"))
	//				bReleaseExists = true;
	//		}
	//	}
	//	
	//	if (!bReleaseExists) {

	//	ActivateSpeedAction->Triggers.Add(ReleaseTriggerA);
	//	}
	//}



	//InvisToggleAction->bConsumeInput = ps->bToggleInvis;



	//UEnhancedInputLibrary::RequestRebuildControlMappingsUsingContext(InputMapping, true);
}
