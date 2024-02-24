// Fill out your copyright notice in the Description page of Project Settings.

#include "BitwiseGameMode.h"
#include "Interactables/ASpawnPowerup.h"
#include "BitwiseGameState.h"
#include "CollectionInteractable.h"
#include "Interactables/XRayVision.h"  
#include "Interactables/InvisibilityPowerup.h"
#include "PlayerCharacter.h"
#include "Math/UnrealMathUtility.h"
#include "BitwiseKey/BitwiseKey.h"
#include "Components/AudioComponent.h" 
#include "PowerupDataBase.h"
#include "Kismet/GameplayStatics.h" 
#include "TimerManager.h"
#include "Kismet/KismetArrayLibrary.h"
#include "UObject/ConstructorHelpers.h" 
#include "BitwiseGameState.h"


ABitwiseGameMode::ABitwiseGameMode()
{

    /** initialize some of the defaults, blueprinting this will override it,
        notice the use of StaticClass to get the UClass class type properly */
    DefaultPawnClass = APlayerCharacter::StaticClass();
    GameStateClass = ABitwiseGameState::StaticClass();


    //static ConstructorHelpers::FClassFinder<UStaticMesh> AssetFile(TEXT("/Game/Blueprints/XRayActor.XRayActor"));
    //if (AssetFile.Class != nullptr) {
    //    WARN("we're so fucking back")
    //    XRayCollectible = AssetFile.Class;

    //}
    //else {
    //    WARN("it's over")
    //}


    //auto xray = ConstructorHelpers::FObjectFinder<AActor>(TEXT("/Game/Blueprints/XRayActor.XRayActor"));
    //if(xray.Succeeded()){
    //    XRayCollectible->
}

void ABitwiseGameMode::BeginPlay()
{

    Super::BeginPlay();
    DispatchBeginPlay();

    playerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPowerup::StaticClass(), PowerupSpawnLocations);

    gs = GetWorld()->GetGameState<ABitwiseGameState>();

    //PlaceCollectibleArray();

    //should probably make a new helper function buuuuuuut


    GetWorldTimerManager().SetTimer(InvisibilityStatStruct.RechargeTimerHandle,
        this, &ABitwiseGameMode::UpdateInvisCharge, 1 / InvisibilityStatStruct.Precision, true, 2.0f);

    GetWorldTimerManager().SetTimer(StaminaStatStruct.RechargeTimerHandle, 
        this, &ABitwiseGameMode::UpdateStamina, 1/ StaminaStatStruct.Precision, true, 2.0f);

    D_OnReset.AddDynamic(this, &ABitwiseGameMode::ResetGameMode);
}



void ABitwiseGameMode::Tick(float DeltaSeconds)
{
    if (IsValid(playerCharacter)) {

        if (playerCharacter->bReceivedFirstPlayerInput) {
            //StartGameTimer();
            gs->gameTimer = GetWorld()->GetUnpausedTimeSeconds() - GameStartTime;
        }
    } else {
        UE_LOG(LogTemp, Error, TEXT("Player character reference in gamemode NOT valid"));
    }
}

void ABitwiseGameMode::StartGameTimer()
{
    GameStartTime = GetWorld()->GetUnpausedTimeSeconds();
    
}

void ABitwiseGameMode::ResetGameMode()
{

    gs->gameTimer = 0;



    //reset ability collection
    for (UPowerupDataBase* powerup : gs->PowerupDataArray) {
        powerup->bCollected = false;
        powerup->bEnabled = false;
    }

    InvisibilityStatStruct.currentCharge = 0; 
    StaminaStatStruct.currentCharge = 0;

    gs->ResetGameState();

    //DEPRECATED: before I refactored powerups to structs I went through and reset each one individually (gross)
    //gs->PowerupMap.Find(EPowerUpName::PE_XRay)->bCollected = false;
    //gs->bHasSpeedBoost = false;
    //gs->bHasJumpBoost = false;
    //gs->bHasInvisibility = false;
    ////make sure that invisibility is reset beyond just collection
    //gs->bPlayerIsInvisible = false;
    //gs->CurrentInvisCharge = 0;

    //DEPRECEATED: before I refactored randomization to be based on individual objects, I'd originally tracked all 
    // the powerups within this game mode. the following comment destroyed their instances. this is now done
    // in RandomizerBase
    //destroy each spawned powerup and remove it from the TMap
    //for ( const auto& Pair : SpawnedCollectiblesMap) {
    //    LOG("PING")
    //    AActor* PowerUpActor = Pair.Value;
    //    PowerUpActor->Destroy();
    //    //SpawnedCollectiblesMap.Remove(Pair.Key);
    //}


    StartGameTimer();
}


void ABitwiseGameMode::CollectXRay()
{
    LOG("collect x ray method called from gamemode");
    gs->XRayData->bCollected = true;
    //used to notify all xray objects to update their state
    OnCollectedXray.Broadcast();
}

//void ABitwiseGameMode::CollectSpeedBoost()
//{
//    gs->SpeedBoostData->bCollected = true;
//}
//
//void ABitwiseGameMode::CollectJumpBoost()
//{
//    gs->JumpBoostStruct.bCollected = true;
//    if (gs->JumpBoostStruct.bPassive) {//if we decide it's a passive ability (rather than one the player must activate)
//        playerCharacter->ActivateJumpBoost();
//    }
//}


void ABitwiseGameMode::ToggleInvisibility()
{

    if (gs->InvisibilityData->bCollected) {

        if (gs->InvisibilityData->bEnabled) {

            gs->InvisibilityData->bEnabled = false;
            UGameplayStatics::PlaySound2D(GetWorld(), SW_InvisDeactivate);


        }
        else {
            gs->InvisibilityData->bEnabled = true;
            UGameplayStatics::PlaySound2D(GetWorld(), SW_InvisActivate);

        }
    }
    else {
        WARN("You do not yet have that ability");
    }
}

void ABitwiseGameMode::UpdateInvisCharge()
{
    if (gs->InvisibilityData->bCollected) {

        //LOG("CurrentCharge: %f", gs->CurrentInvisCharge)
        if (gs->InvisibilityData->bEnabled) { //invisibility active, counting down

            InvisibilityStatStruct.currentCharge = FMath::Clamp(
                InvisibilityStatStruct.currentCharge - (InvisibilityStatStruct.DischargeRate / InvisibilityStatStruct.Precision),
                0.0, InvisibilityStatStruct.MaxCharge);

            if (InvisibilityStatStruct.currentCharge == 0) {
                ToggleInvisibility();
                return;
            }

            //DEPRECATED: the (obviously very messy) way I'd been clamping the values originally
            //if (InvisibilityStruct.currentCharge == 0) {
            //    ToggleInvisibility();
            //    return;
            //}
            //else  if (InvisibilityStruct.currentCharge < 0) {
            //    InvisibilityStruct.currentCharge = 0;
            //    return;
            //}
            //else if (InvisibilityStruct.currentCharge > 0) {
            //    InvisibilityStruct.currentCharge -= InvisibilityStruct.DischargeRate / InvisibilityStruct.Precision;
            //    return;
            //}
        } else { //invisibility inactive, counting up

            InvisibilityStatStruct.currentCharge = FMath::Clamp(
                InvisibilityStatStruct.currentCharge + (InvisibilityStatStruct.ChargeRate / InvisibilityStatStruct.Precision),
                0.0, InvisibilityStatStruct.MaxCharge);
                
            //DEPRECATED: the (obviously very messy) way I'd been clamping the values originally
            //if (InvisibilityStruct.currentCharge == InvisibilityStruct.MaxCharge) {
            //    return;
            //}
            //else  if (InvisibilityStruct.currentCharge > InvisibilityStruct.MaxCharge) {
            //    InvisibilityStruct.currentCharge = InvisibilityStruct.MaxCharge;
            //    return;
            //}
            //else if (gs->CurrentInvisCharge < InvisMaxCharge) {
            //    gs->CurrentInvisCharge += InvisChargeRate/ProgressBarPrecision;
            //    return;
            //}
        }
    }
    return ;
}

void ABitwiseGameMode::UpdateStamina()
{
    if (gs->GetHasStaminaAbility()) {
        if (gs->GetPlayerIsUsingStamina()) { //count down

            //decrease the value, setting it no lower than 0 and no higher than the max
            StaminaStatStruct.currentCharge = FMath::Clamp(
                StaminaStatStruct.currentCharge - (StaminaStatStruct.DischargeRate / StaminaStatStruct.Precision),
                0.0, StaminaStatStruct.MaxCharge);

            if (StaminaStatStruct.currentCharge == 0) {
                playerCharacter->DeactivateStaminaEffects(); //tell the player to deactivate stamina
                return;
            }

            //DEPRECATED
            //if (gs->CurrentStamina == 0) {
            //    ToggleStamina();
            //    return;
            //}
            //else  if (gs->CurrentStamina < 0) {
            //    gs->CurrentStamina = 0;
            //    return;
            //}
            //else if (gs->CurrentStamina > 0) {

            //    gs->CurrentStamina -= StaminaDischargeRate / ProgressBarPrecision;
            //    return;
            //}
        }
        else { //invisibility inactive, counting up

            //increase stamina, setting it no lower than 0 and no higher than the max
            StaminaStatStruct.currentCharge = FMath::Clamp(
                StaminaStatStruct.currentCharge + (StaminaStatStruct.ChargeRate / StaminaStatStruct.Precision),
                0.0, StaminaStatStruct.MaxCharge);


            //if (gs->CurrentStamina == InvisMaxCharge) {
            //    return;
            //}
            //else  if (gs->CurrentStamina > InvisMaxCharge) {
            //    gs->CurrentStamina = InvisMaxCharge;
            //    return;
            //}
            //else if (gs->CurrentStamina < InvisMaxCharge) {
            //    gs->CurrentStamina += InvisChargeRate / ProgressBarPrecision;
            //    return;
            //}
        }
    }
}



