// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/BitwisePlayerController.h"
#include "Managers/BitwisePlayerController.h"
#include "Managers/BitwisePlayerState.h"
#include "CustomGameState.h"
#include "GameFramework/PlayerState.h"
#include "EnhancedInputComponent.h"
#include "Managers/BitwisePlayerState.h"
#include "Milestones/Milestones.h"
#include "PlayerCharacter.h"
#include "CustomGameMode.h"
#include "Managers/BitwisePlayerController.h"

#include "Kismet/GameplayStatics.h" 


bool ABitwisePlayerController::UpdateInvisCharge()
{
	return false;
}

void ABitwisePlayerController::BeginPlay()
{
	Super::BeginPlay();

	gm = GetWorld()->GetAuthGameMode<ACustomGameMode>();
	gs = Cast<ACustomGameState>(gm->GameState);
	//pc = Cast<ABitwisePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	ps = this->GetPlayerState<ABitwisePlayerState>();
	playerCharacter = Cast<APlayerCharacter>(gm->DefaultPawnClass.GetDefaultObject());
	if (IsValid(playerCharacter)) {
		WARN("Player character is valid from controller")
	}
	else {
		WARN("Player character is NOT valid from controller")

	}

	SetupInputComponent();
	
}

void ABitwisePlayerController::PlayerTick(float DeltaTime)
{
}

void ABitwisePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	WARN("controller calling SetupInputComponent")
	if (IsValid(InputComponent)) {
		if (IsValid(playerCharacter)) {
			playerCharacter->SetupPlayerInputComponent(InputComponent);		
			WARN("setupPlayerInputComponet successfully called on playercharacter from PlayerController")
		}
		else {
			WARN("player character not valid")
		}
	}
	else {

		WARN("input Component  not valid")
	}
}
