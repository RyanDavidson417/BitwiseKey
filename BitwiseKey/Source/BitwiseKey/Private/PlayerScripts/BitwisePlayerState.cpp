// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerScripts/BitwisePlayerState.h"
#include "BitwiseKey/BitwiseKey.h"
#include "Kismet/GameplayStatics.h"
#include "Core/BitwiseGameMode.h"
#include "PlayerScripts/PlayerCharacter.h"
#include "Core/OptionsSaveGame.h"
#include "Core/BitwiseGameState.h"

void ABitwisePlayerState::BeginPlay()
{
	gs = Cast<ABitwiseGameState>(UGameplayStatics::GetGameState(this));
	gm = GetWorld()->GetAuthGameMode<ABitwiseGameMode>();

	if (UGameplayStatics::DoesSaveGameExist(gs->OptionsSlotName, 0)) {
		if (sg = Cast<UOptionsSaveGame>(UGameplayStatics::LoadGameFromSlot(gs->OptionsSlotName, 0))) {

			LOG("save game found")
				UpdatePlayerOptions(sg);
		}
	}
	else {
		LOG("game state does not exist")
	}

	gm->FOnOptionsChangeDelegate.AddUniqueDynamic(this, &ABitwisePlayerState::UpdatePlayerOptions);
}



void ABitwisePlayerState::UpdatePlayerOptions(UOptionsSaveGame* SaveGame)
{
	LOG("delegate updating look controls")
	bInvertXAxis = SaveGame->bInvertXAxis;
	bInvertYAxis = SaveGame->bInvertYAxis;

	fXSensitivity = SaveGame->fXSensitivity;
	fYSensitivity = SaveGame->fYSensitivity;

	bToggleSprint = SaveGame->ToggleSprint;
	bToggleInvis = SaveGame->ToggleInvis;

	gm->PlayerCharacter->UpdateToggles();

}