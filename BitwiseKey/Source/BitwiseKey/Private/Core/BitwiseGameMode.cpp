// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/BitwiseGameMode.h"
#include "Interactables/ASpawnPowerup.h"
#include "Core/BitwiseGameState.h"
#include "LevelObjects/CollectionInteractable.h"
#include "Interactables/XRayVision.h"  
#include "Interactables/InvisibilityPowerup.h"
#include "PlayerScripts/PlayerCharacter.h"
#include "Math/UnrealMathUtility.h"
#include "BitwiseKey/BitwiseKey.h"
#include "Core/OptionsSaveGame.h"
#include "Components/AudioComponent.h" 
#include "LevelObjects/PowerupDataBase.h"
#include "Kismet/GameplayStatics.h" 
#include "TimerManager.h"
#include "Kismet/KismetArrayLibrary.h"
#include "UObject/ConstructorHelpers.h" 
#include "Core/BitwiseGameState.h"


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

    //if (UGameplayStatics::DoesSaveGameExist(gs->OptionsSlotName, 0)) {
    //    if( UOptionsSaveGame* sg = (UGameplayStatics::LoadGameFromSlot(gs->OptionsSlotName, 0))){
    //        FOnOptionsChangeDelegate.Broadcast(sg);
    //    }
    //}



    PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPowerup::StaticClass(), PowerupSpawnLocations);

    gs = GetWorld()->GetGameState<ABitwiseGameState>();

    //PlaceCollectibleArray();

    //should probably make a new helper function buuuuuuut

    if (UGameplayStatics::DoesSaveGameExist(gs->OptionsSlotName, 0)) {
        if (UOptionsSaveGame* sg = Cast<UOptionsSaveGame>(UGameplayStatics::LoadGameFromSlot(gs->OptionsSlotName, 0))) {

            LOG("save game found")
            FOnOptionsChangeDelegate.Broadcast(sg);
        }
            
    }
    else {
        //save game not found, default to toggle
        LOG("save game not found")
    }

    GetWorldTimerManager().SetTimer(InvisibilityStatStruct.RechargeTimerHandle,
        this, &ABitwiseGameMode::UpdateInvisCharge, 1 / InvisibilityStatStruct.Precision, true, 2.0f);

    GetWorldTimerManager().SetTimer(StaminaStatStruct.RechargeTimerHandle, 
        this, &ABitwiseGameMode::UpdateStamina, 1/ StaminaStatStruct.Precision, true, 2.0f);

    bGameTimerRunning = true;

    D_OnReset.AddDynamic(this, &ABitwiseGameMode::ResetGameMode);



}



void ABitwiseGameMode::Tick(float DeltaSeconds)
{
    if (IsValid(PlayerCharacter)) {

        if (PlayerCharacter->bReceivedFirstPlayerInput && bGameTimerRunning) {
            //StartGameTimer();
            gs->gameTimer += DeltaSeconds;
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


    bGameTimerRunning = true;
    StartGameTimer();
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


void ABitwiseGameMode::CollectXRay()
{
    LOG("SHOULD BE ONCE")
    gs->XRayData->bCollected = true;
    //used to notify all xray objects to update their state
    OnCollectedXray.Broadcast();
    OnCollectedAbilityDelegate.Broadcast(EPowerUpName::PE_XRay);

}

void ABitwiseGameMode::CollectInvisibility()
{
    gs->InvisibilityData->bCollected = true;
    OnCollectedAbilityDelegate.Broadcast(EPowerUpName::PE_Invisibility);
}

void ABitwiseGameMode::CollectSpeedBoost()
{
    gs->SpeedBoostData->bCollected = true;
    OnCollectedAbilityDelegate.Broadcast(EPowerUpName::PE_SpeedBoost);
}

void ABitwiseGameMode::CollectJumpBoost()
{
    gs->JumpBoostData->bCollected = true;
    OnCollectedAbilityDelegate.Broadcast(EPowerUpName::PE_JumpBoost);
}


void ABitwiseGameMode::StopGameTimerAndMusic()
{
    bGameTimerRunning = false;
    OnMusicStop.Broadcast();
}

void ABitwiseGameMode::PauseGameMode()
{
    OnGamePause.Broadcast();
}

void ABitwiseGameMode::UnPauseGameMode()
{
    OnGameUnPause.Broadcast();
}


#pragma region invis
void ABitwiseGameMode::UpdateInvisCharge()
{
    if (gs->InvisibilityData->bCollected) {

        //LOG("CurrentCharge: %f", gs->CurrentInvisCharge)
        if (gs->InvisibilityData->bEnabled) { //invisibility active, counting down
            


            InvisibilityStatStruct.currentCharge = FMath::Clamp(
                InvisibilityStatStruct.currentCharge - (InvisibilityStatStruct.DischargeRate / InvisibilityStatStruct.Precision),
                0.0, InvisibilityStatStruct.MaxCharge);

            if (InvisibilityStatStruct.currentCharge == 0) {
                DeactivateInvisibility(true);
                return;
            }

        } else { //invisibility inactive, counting up


            //calculate whether the invis recharge delay has passed
            float CurrentTime = UGameplayStatics::GetUnpausedTimeSeconds(this);
            float TimeInvisCanActivate = TimeSinceInvisRechargeStart + CurrentInvisRechargeDelay;
            if (CurrentTime > TimeInvisCanActivate) {//if the delay has passed

                //increase invis, setting it no lower than 0 and no higher than the max
                InvisibilityStatStruct.currentCharge = FMath::Clamp(
                    InvisibilityStatStruct.currentCharge + (InvisibilityStatStruct.ChargeRate / InvisibilityStatStruct.Precision),
                    0.0, InvisibilityStatStruct.MaxCharge);
            }
                
           
        }
    }
    return;
}


void ABitwiseGameMode::ToggleInvisibility()
{

    if (gs->InvisibilityData->bEnabled) {
        DeactivateInvisibility();
    }
    else {
        ActivateInvisibility();
    }

}

void ABitwiseGameMode::ActivateInvisibility()
{
    //zzz check all refs to invis data to ensure this is the only time we're using it
    if (gs->InvisibilityData->bCollected) {
        if (InvisibilityStatStruct.currentCharge) {
            gs->InvisibilityData->bEnabled = true;

            if (IsValid(PlayerCharacter)) {
                PlayerCharacter->ActivateInvisibilityVFX();
            }
            else {
                ERROR("gamemode reference to PlayerCharacter NOT VALID")
            }
        }
    }
    else {
        LOG("you do not yet have that ability");
    }

}

void ABitwiseGameMode::DeactivateInvisibility(bool bRanFullyOut)
{
    TimeSinceInvisRechargeStart = UGameplayStatics::GetUnpausedTimeSeconds(this);
    if (bRanFullyOut) {
        CurrentInvisRechargeDelay = FullyOutRechargeDelay;
    }
    else { //make the player wait longer if they ran all the way out
        CurrentInvisRechargeDelay = DefaultRechargeDelay;
    }

    gs->InvisibilityData->bEnabled = false;
    if (IsValid(PlayerCharacter)) {

        PlayerCharacter->DeactivateInvisibilityVFX(bRanFullyOut);
    }
    else {
        ERROR("gamemode reference to PlayerCharacter NOT VALID")
    }
}



#pragma endregion invis

#pragma region stamina
void ABitwiseGameMode::UpdateStamina()
{
    if (gs->GetHasStaminaAbility()) {
        if (gs->GetPlayerIsUsingStamina()) { //count down

            //decrease the value, setting it no lower than 0 and no higher than the max
            StaminaStatStruct.currentCharge = FMath::Clamp(
                StaminaStatStruct.currentCharge - (StaminaStatStruct.DischargeRate / StaminaStatStruct.Precision),
                0.0, StaminaStatStruct.MaxCharge);

            //deactivate stamina

            if (StaminaStatStruct.currentCharge == 0) {
                DeactivateStamina(true);
                return;
            }

        } else { //invisibility inactive, counting up
            
            //calculate whether the stamina delay has passed
            float CurrentTime = UGameplayStatics::GetUnpausedTimeSeconds(this);
            float TimeStaminaCanActivate = TimeSinceStaminaRechargeStart + CurrentStaminaRechargeDelay;
            if (CurrentTime > TimeStaminaCanActivate) {//if the delay has passed

                //increase stamina, setting it no lower than 0 and no higher than the max
                StaminaStatStruct.currentCharge = FMath::Clamp(
                    StaminaStatStruct.currentCharge + (StaminaStatStruct.ChargeRate / StaminaStatStruct.Precision),
                    0.0, StaminaStatStruct.MaxCharge);        
            }
        }
    }
}

void ABitwiseGameMode::ToggleStamina()
{
    if (gs->SpeedBoostData->bEnabled) {
        DeactivateStamina();
    }
    else {
        ActivateStamina();
    }
}


void ABitwiseGameMode::ActivateStamina()
{
    if (gs->SpeedBoostData->bCollected) {
        if (StaminaStatStruct.currentCharge > 0) {
            gs->SpeedBoostData->bEnabled = true;
            PlayerCharacter->ActivateStaminaEffects();
        }
    }
    else {
        LOG("you do not yet have that ability")
    }



    //call to player to activate stamina fx
}

void ABitwiseGameMode::DeactivateStamina(bool bRanFullyOut)
{

    TimeSinceStaminaRechargeStart = UGameplayStatics::GetUnpausedTimeSeconds(this);
    if (bRanFullyOut) {
        CurrentStaminaRechargeDelay = FullyOutRechargeDelay;
    }
    else {
        CurrentStaminaRechargeDelay = DefaultRechargeDelay;
    }
    gs->SpeedBoostData->bEnabled = false;

    PlayerCharacter->DeactivateStaminaEffects(bRanFullyOut);

}

#pragma endregion Stamina

