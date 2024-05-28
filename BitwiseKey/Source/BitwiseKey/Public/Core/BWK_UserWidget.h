// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BWK_UserWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BITWISEKEY_API UBWK_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void HideMenu(); // no C++ implementation

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnStartButtonPressed(); //no c++ implementation - "overriden" by blueprints
	virtual void OnStartButtonPressed_Implementation();

};
