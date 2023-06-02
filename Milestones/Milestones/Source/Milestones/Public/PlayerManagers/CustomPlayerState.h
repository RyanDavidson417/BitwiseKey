// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CustomPlayerState.generated.h"

/**
 * 
 */


class ACustomGameMode;
class APlayerCharacter;
class ACustomGameState;
class ACustomPlayerController;

UCLASS()
class MILESTONES_API ACustomPlayerState : public APlayerState
{
	GENERATED_BODY()

public:


	TObjectPtr<ACustomGameState> gs;
	TObjectPtr<ACustomPlayerController> pc;
	TObjectPtr<ACustomPlayerState> ps;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Powerups")
		bool bPlayerIsInvisible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
		float CurrentInvisCharge;

	
};
