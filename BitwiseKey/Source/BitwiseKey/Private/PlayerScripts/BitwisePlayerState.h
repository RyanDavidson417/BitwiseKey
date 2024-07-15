// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BitwisePlayerState.generated.h"

class UOptionsSaveGame;
class ABitwiseGameState;
class ABitwiseGameMode;

/**
 * 
 */
UCLASS()
class ABitwisePlayerState : public APlayerState
{
	GENERATED_BODY()

private:

	TObjectPtr<UOptionsSaveGame> sg;
	TObjectPtr<ABitwiseGameState> gs;
	TObjectPtr<ABitwiseGameMode> gm;


	UFUNCTION()
	void UpdatePlayerOptions(UOptionsSaveGame* SaveGame);

protected:


public:

	bool bInvertXAxis;

	bool bInvertYAxis;

	float fXSensitivity = 1;
	float fYSensitivity = 1;

	bool bToggleSprint = true;
	bool bToggleInvis = true;


	UFUNCTION()
	void BeginPlay() override;


};
