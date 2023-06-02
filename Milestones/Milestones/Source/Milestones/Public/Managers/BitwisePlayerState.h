// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BitwisePlayerState.generated.h"

/**
 * 
 */

class ACustomGameMode;
class APlayerCharacter;
class ACustomGameState;
class ABitwisePlayerController;

UCLASS()
class MILESTONES_API ABitwisePlayerState : public APlayerState
{
	GENERATED_BODY()
	

public:

    TObjectPtr<ACustomGameState> gs;//might be unecessary 
    TObjectPtr<ABitwisePlayerController> pc;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Powerups")
        bool bPlayerIsInvisible;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
        float CurrentInvisCharge;


};
