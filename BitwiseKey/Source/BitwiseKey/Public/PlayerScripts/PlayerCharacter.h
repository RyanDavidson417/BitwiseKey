// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interactables/InteractionComponent.h"
#include "LevelObjects/CollectionInteractable.h"
#include "Core/BitwiseGameMode.h"
#include "Core/BitwiseGameState.h"
#include "PlayerCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class UCharacterMovementComponent;
class UInteractionComponent;
class UCollectionInteractable;
class ABitwiseGameMode;
class UPowerupDataBase;
class ABitwiseGameState;
class UAudioComponent;
class UBWK_UserWidget;
class ABitwisePlayerState;
class UOptionsSaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFovChangeSignature, int32, TargetFov);

UCLASS()
class BITWISEKEY_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

//variables
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	bool bReceivedFirstPlayerInput;


	//set from traceline when we find an interactable
	UPROPERTY(VisibleAnywhere, blueprintReadOnly, Category = Interaction)
	UInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UBWK_UserWidget> CurrentWidget;

protected:



	//gamemode and gamestate, playercontroller and playerstate will be declared here as well
	TObjectPtr<ABitwiseGameMode> gm;
	TObjectPtr<ABitwiseGameState> gs;

	//references to the actions 
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
	/** Reset Player Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		class UInputAction* ResetPlayerAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		class UInputAction* ActivateSpeedAction;

	//movement and look input variables, set in move and look functions
	FVector2d lastLookInput;
	FVector2D lastMoveInput;

	//the base input mapping context we want to add
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputMappingContext* InputMapping;

	//first person camera
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(BlueprintAssignable)
	FOnFovChangeSignature FOnFOVIncreaseDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnFovChangeSignature FOnFOVDecreaseDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = Camera)
	int DefaultFOV = 90;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = Camera)
	int SprintingFOV = 100;

	//max movement speed
	UPROPERTY(EditAnywhere)
		float MaxMoveSpeed;

	//interaction variables
	UPROPERTY(EditAnywhere)
		float interactionDistance;

		UCharacterMovementComponent* CharacterMovement;
	//whether or not we've hit an actor (maybe needs to be a collectible?
	FHitResult LineTraceHit;

	// You can expose some of your collision query data as properties to help customize and debug 
	// Here we expose the collision channel we want to run the query on, and set it to only hit Pawns.
	UPROPERTY(EditAnywhere, Category = "Collision")
		TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;

	//reference to camera component
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	bool bStaminaActive = false;

	UPROPERTY(BlueprintReadOnly)
	FRotator RandomStartingRotation;

	TObjectPtr<UOptionsSaveGame> OptionsSaveGame;

	//methods
public:

	// Sets default values for this character's properties
	APlayerCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//update movement and looking
	void Move(const struct FInputActionInstance& Instance);
	void StopMoving(const struct FInputActionInstance& Instance);
	void Look(const FInputActionInstance& InputActionInstance);

	void Jump() override;

	//interaction
	void Interact(const FInputActionInstance& Instance);

	void TraceLine();

	//powerups



	void ToggleInvisibility(const FInputActionInstance& Instance);
	
	void ToggleStamina();
	void ActivateStaminaEffects();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "DeactivateStaminaEffects"))
	void DeactivateStaminaEffects(bool bRanFullyOut = false);
	virtual void DeactivateStaminaEffects_Implementation(bool bRanFullyOut = false);

	void ActivateJumpBoost();
	void DeactivateJumpBoost();

	UFUNCTION(BlueprintImplementableEvent)
	void ActivateInvisibilityVFX(); //no c++ implementation
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DeactivateInvisibilityVFX(bool bRanFullyOut = false);
	

	UFUNCTION(BlueprintImplementableEvent)
	void PlayMovementSound(int IsWalking); //no ++ implementation
	UFUNCTION(BlueprintImplementableEvent)
	void StopMovementSound(); //no ++ implementation
	
	UFUNCTION()
	void ResetPlayer();


	UFUNCTION(BlueprintImplementableEvent)
	void DisplayInteractPrompt(); //no C++ implementation

	void ResetFromPlayer();

	void UpdateToggles();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	void setRandomStartRotation();

	UPROPERTY(EditAnywhere, category = "audio")
	TObjectPtr<USoundBase> FirstJumpSound;

	UPROPERTY(EditAnywhere, category = "audio")
	TObjectPtr<USoundBase> DoubleJumpSound;

	UPROPERTY(EditAnywhere, category = "audio")
	TObjectPtr<USoundBase> WalkingAudio;

	UPROPERTY(EditAnywhere, category = "audio")
	TObjectPtr<USoundBase> SprintingAudio;

	UPROPERTY(EditAnywhere, category = "audio")
	TObjectPtr<USoundBase> SprintStartAudio;

	UPROPERTY(EditAnywhere, category = "audio")
	TObjectPtr<USoundBase> SprintEndAudio;

	UPROPERTY(EditAnywhere, category = "audio")
	TObjectPtr<USoundBase> StaminaOutAudio;

	TObjectPtr<UAudioComponent> CurrentMovementAudioComponent;
	TObjectPtr<UAudioComponent> WalkingAudioComponent;
	TObjectPtr<UAudioComponent> SprintingAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category= "audio")
	TObjectPtr<UAudioComponent> InvisHumAudio;


	//sound waves to play when you activate and deactivate invisibility
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
	USoundWave* SW_InvisActivate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
	USoundWave* SW_InvisDeactivate;


	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> M_RippleEffectBase;

	TObjectPtr<UMaterialInstanceDynamic> MiD_RippleEffect;
	


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectibles")
	TMap<EPowerUpName, FPowerupStruct> StaminaPowerups;

	bool bIsMoving = false;


	float DefaultAirControl;



	TObjectPtr<ABitwisePlayerState> ps;

};
