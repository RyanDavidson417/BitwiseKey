// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BitwisePlayerController.generated.h"

/**
 * 
 */


class ACustomGameMode;
class APlayerCharacter;
class ACustomGameState;
class ABitwisePlayerState;


UCLASS()
class MILESTONES_API ABitwisePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    bool UpdateInvisCharge();
    virtual void BeginPlay() override;
    virtual void PlayerTick(float DeltaTime) override;
    virtual void SetupInputComponent() override; //may not need this

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
        float InvisMaxCharge;


    TObjectPtr<ACustomGameMode> gm;
    TObjectPtr<ACustomGameState> gs;
    TObjectPtr<ABitwisePlayerState> ps;
    //APlayerCharacter* playerCharacter;
    TObjectPtr<APlayerCharacter> playerCharacter;


protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
        float InvisIncrement;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
        float InvisDecrement;


};
