// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "OptionsSaveGame.generated.h"


/**
 * 
 */
UCLASS()
class BITWISEKEY_API UOptionsSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	bool bInvertXAxis;

	UPROPERTY(BlueprintReadWrite)
	bool bInvertYAxis;


	UPROPERTY(BlueprintReadWrite)
	float fXSensitivity;

	UPROPERTY(BlueprintReadWrite)
	float fYSensitivity;


	UPROPERTY(BlueprintReadWrite)
	bool ToggleInvis;


	UPROPERTY(BlueprintReadWrite)
	bool ToggleSprint;

};
