// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerScripts/BitwisePlayerState.h"
#include "BitwiseKey/BitwiseKey.h"
#include "Kismet/GameplayStatics.h"
#include "Core/BitwiseGameMode.h"
#include "Core/OptionsSaveGame.h"
#include "Core/BitwiseGameState.h"

void ABitwisePlayerState::BeginPlay()
{
	gs = Cast<ABitwiseGameState>(UGameplayStatics::GetGameState(this));
	gm = GetWorld()->GetAuthGameMode<ABitwiseGameMode>();

	if (UGameplayStatics::DoesSaveGameExist(gs->OptionsSlotName, 0)) {
		UGameplayStatics::LoadGameFromSlot(gs->OptionsSlotName, 0);
	}
	else {
		LOG("game state does not exist")
	}

	gm->FOnOptionsChangeDelegate.AddUniqueDynamic(this, &ABitwisePlayerState::UpdateLookControls);
}



void ABitwisePlayerState::UpdateLookControls(UOptionsSaveGame* SaveGame)
{
	LOG("delegate updating look controls")
	bInvertXAxis = SaveGame->bInvertXAxis;
	bInvertYAxis = SaveGame->bInvertYAxis;

	fXSensitivity = SaveGame->fXSensitivity;
	fYSensitivity = SaveGame->fYSensitivity;
}