// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomGameState.h"
#include "GameFramework/PlayerState.h"
#include "EnhancedInputComponent.h"
#include "PlayerManagers/CustomPlayerState.h"
#include "Milestones/Milestones.h"
#include "PlayerCharacter.h"
#include "CustomGameMode.h"
#include "PlayerManagers/CustomPlayerController.h"



void ACustomPlayerController::BeginPlay()
{
	gm = GetWorld()->GetAuthGameMode<ACustomGameMode>();
	gs = Cast<ACustomGameState>(gm->GameState);
	//gs = GetWorld()->GetGameState<ACustomGameState>();
	ps = this->GetPlayerState<ACustomPlayerState>();
	playerCharacter = Cast<APlayerCharacter>(gm->DefaultPawnClass);
}

void ACustomPlayerController::PlayerTick(float deltaTime)
{
	updateInvisCharge();
	LOG("Current invis charge: %f", ps->CurrentInvisCharge)
}

void ACustomPlayerController::SetupInputComponent()
{
	//Super::SetupInputComponent(); //commented cause it was breaking it
	UEnhancedInputComponent* EIS;

	UE_LOG(LogTemp, Warning, TEXT("running SetupPlayerComponent()"));
	//WARN("getting enhanced input component");
	//doncasting the PlayerInputComponent to be a UEnhancedInputComponent
	if (IsValid(playerCharacter->InputComponent)) {
		
		WARN("INPUT COMP SUCC")
		/*
		 EIS = CastChecked<UEnhancedInputComponent>(playerCharacter->InputComponent);

		//bind the move action
		//WARN("Binding Move actions");
		//UE_LOG(LogTemp, Warning, TEXT("binding the move action"));
		EIS->BindAction(MovementAction, ETriggerEvent::Triggered, playerCharacter, &APlayerCharacter::Move);
			//MovementAction, ETriggerEvent::Triggered, playerCharacter, &APlayerCharacter::Move);
		//bind the steer action
		EIS->BindAction(LookAction, ETriggerEvent::Triggered, playerCharacter, &APlayerCharacter::Look);
		//bind the Interact action
		EIS->BindAction(InteractAction, ETriggerEvent::Started, playerCharacter, &APlayerCharacter::Interact);
		//bind the invisActivate action;
		EIS->BindAction(InvisToggleAction, ETriggerEvent::Started, playerCharacter, &APlayerCharacter::ToggleInvisibility);


		//bind the jump actions
		EIS->BindAction(JumpAction, ETriggerEvent::Triggered, playerCharacter, &ACharacter::Jump);
		EIS->BindAction(JumpAction, ETriggerEvent::Completed, playerCharacter, &ACharacter::StopJumping);
		*/
	}
	else {
		WARN("INPUT COMPONENT FAILED")
	}
	//UEnhancedInputComponent* EIS = CastChecked<UEnhancedInputComponent>(InputComponent);//previous version




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
