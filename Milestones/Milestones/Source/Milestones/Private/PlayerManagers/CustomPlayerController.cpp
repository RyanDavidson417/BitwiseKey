// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerManagers/CustomPlayerController.h"
#include "CustomGameState.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerManagers/CustomPlayerState.h"
#include "Milestones/Milestones.h"
#include "PlayerCharacter.h"
#include "CustomGameMode.h"


ACustomPlayerController::ACustomPlayerController()
{
}


void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();


	gm = GetWorld()->GetAuthGameMode<ACustomGameMode>();
	gs = Cast<ACustomGameState>(gm->GameState);
	//gs = GetWorld()->GetGameState<ACustomGameState>();
	ps = this->GetPlayerState<ACustomPlayerState>();
	playerCharacter = Cast<APlayerCharacter>(gm->DefaultPawnClass.GetDefaultObject());

	//add input mapping context
	if (APlayerController* playerController = Cast<APlayerController>(this))
	{

		//UE_LOG(LogTemp, Warning, TEXT("checking to see if there's a local player"));
		if (ULocalPlayer* localPlayer = Cast<ULocalPlayer>(playerController->GetLocalPlayer()))
		{
			//UE_LOG(LogTemp, Warning, TEXT("looking for input system "));
			if (UEnhancedInputLocalPlayerSubsystem* inputSystem =
				localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				//UE_LOG(LogTemp, Warning, TEXT("loading inputMapping"));
				if (playerCharacter->InputMapping != nullptr)
				{

					UE_LOG(LogTemp, Warning, TEXT("reached end of playerController nested ifs"));
					//UE_LOG(LogTemp, Warning, TEXT("adding mapping context"));
					inputSystem->AddMappingContext(playerCharacter->InputMapping, 0);
				}
			}
		}
	}

	SetupInputComponent();
	
}

void ACustomPlayerController::PlayerTick(float deltaTime)
{
	updateInvisCharge();
	//LOG("Current invis charge: %f", ps->CurrentInvisCharge)
}

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IsValid(playerCharacter)) {
		//Super::SetupInputComponent(); //commented cause it was breaking it
		UEnhancedInputComponent* EIS = CastChecked<UEnhancedInputComponent>(InputComponent);

		//WARN("getting enhanced input component");
		//doncasting the PlayerInputComponent to be a UEnhancedInputComponent

		UE_LOG(LogTemp, Warning, TEXT("running SetupPlayerComponent()"));

		//bind the move action
		//WARN("Binding Move actions");
		//UE_LOG(LogTemp, Warning, TEXT("binding the move action"));


			//EIS->BindAction(MovementAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		EIS->BindAction(MovementAction, ETriggerEvent::Triggered, this, GET_FUNCTION_NAME_CHECKED(ACustomPlayerController, MovePlayer));


		//	//MovementAction, ETriggerEvent::Triggered, playerCharacter, &APlayerCharacter::Move);
		////bind the steer action //ACustomPlayerController::MovePlayer
		//EIS->BindAction(LookAction, ETriggerEvent::Triggered, playerCharacter, &APlayerCharacter::Look);
		////bind the Interact action
		//EIS->BindAction(InteractAction, ETriggerEvent::Started, playerCharacter, &APlayerCharacter::Interact);
		////bind the invisActivate action;
		//EIS->BindAction(InvisToggleAction, ETriggerEvent::Started, playerCharacter, &APlayerCharacter::ToggleInvisibility);


		////bind the jump actions
		//EIS->BindAction(JumpAction, ETriggerEvent::Triggered, playerCharacter, &ACharacter::Jump);
		//EIS->BindAction(JumpAction, ETriggerEvent::Completed, playerCharacter, &ACharacter::StopJumping);
		//UEnhancedInputComponent* EIS = CastChecked<UEnhancedInputComponent>(InputComponent);//previous version

	}
	else {
		WARN("CustomPlayerController.SetupPlayerComonent() called but playerCharacter was not valid")
	}

}


void ACustomPlayerController::MovePlayer(const FInputActionInstance& InputActionInstance)
{
	WARN("MOVEPLAYER CALLED")
	//playerCharacter->Move(InputActionInstance);
}



//returns true if any changes are made to the charge
bool ACustomPlayerController::updateInvisCharge()
{
	if (gs->hasInvisibility) {

		bool bLocalPlayerIsInvisible = ps->bPlayerIsInvisible;
		if (bLocalPlayerIsInvisible) {
			if (ps->CurrentInvisCharge == 0) {
				return false;
			}
			else  if (ps->CurrentInvisCharge < 0) {
				ps->CurrentInvisCharge = 0;
				return true;
			}
			else if (ps->CurrentInvisCharge > 0) {

				ps->CurrentInvisCharge -= InvisDecrement;
				return true;
			}
		} else {
			if (ps->CurrentInvisCharge == InvisMaxCharge) {
				return false;
			}
			else  if (ps->CurrentInvisCharge > InvisMaxCharge) {
				ps->CurrentInvisCharge = InvisMaxCharge;
				return true;
			}
			else if (ps->CurrentInvisCharge < InvisMaxCharge) {
				
				ps->CurrentInvisCharge += InvisIncrement;
				return true;
			}
		}
		
	}
	return false;
}
