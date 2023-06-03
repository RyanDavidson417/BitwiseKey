// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

/**
 * 
 */

class ACustomGameMode;
class APlayerCharacter;
class ACustomGameState;
class ACustomPlayerState;
class APlayerCharacter;
class UEnhancedInputComponent;


UCLASS()
class MILESTONES_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACustomPlayerController();
	bool updateInvisCharge();
	void BeginPlay() override;
	void PlayerTick(float deltaTime) override;
	virtual void SetupInputComponent() override;

	//void MovePlayer(const struct FInputActionInstance& InputActionInstance);
	void MovePlayer();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
		float InvisMaxCharge;


	//the base input mapping context we want to add
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputMappingContext* InputMapping;

	//references to the actions 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* TestAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* LookAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		class UInputAction* JumpAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		class UInputAction* InteractAction;


	/** InvisToggle Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		class UInputAction* InvisToggleAction;



	TObjectPtr<ACustomGameMode> gm;
	TObjectPtr<ACustomGameState> gs;
	TObjectPtr<ACustomPlayerState> ps;
	TObjectPtr<APlayerCharacter> playerCharacter;
	//TObjectPtr<APlayerCharacter> playerCharacter //throws an error when binding movement input actions

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
		float InvisIncrement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerups")
		float InvisDecrement;


};
