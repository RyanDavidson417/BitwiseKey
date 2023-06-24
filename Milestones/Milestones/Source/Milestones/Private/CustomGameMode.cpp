// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomGameMode.h"
#include "Interactables/ASpawnPowerup.h"
#include "CustomGameState.h"
#include "CollectionInteractable.h"
#include "Interactables/XRayVision.h"  
#include "Interactables/InvisibilityPowerup.h"
#include "PlayerCharacter.h"
#include "Math/UnrealMathUtility.h"
#include "Milestones/Milestones.h"
#include "Kismet/GameplayStatics.h" 
#include "TimerManager.h"
#include "Kismet/KismetArrayLibrary.h"
#include "UObject/ConstructorHelpers.h" 
#include "CustomGameState.h"


ACustomGameMode::ACustomGameMode()
{

    /** initialize some of the defaults, blueprinting this will override it,
        notice the use of StaticClass to get the UClass class type properly */
    DefaultPawnClass = APlayerCharacter::StaticClass();
    GameStateClass = ACustomGameState::StaticClass();


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

void ACustomGameMode::BeginPlay()
{

    Super::BeginPlay();
    DispatchBeginPlay();

    playerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPowerup::StaticClass(), PowerupSpawnLocations);

    gs = GetWorld()->GetGameState<ACustomGameState>();
    randomizePowerups();

    PlaceCollectibleArray();

    //should probably make a new helper function buuuuuuut

    //
    GetWorldTimerManager().SetTimer(InvisRechargeTimerHandle, this, &ACustomGameMode::updateInvisCharge, 1/invis_precision, true, 2.0f);

    LOG("size of array = %f", SpawnedCollectibles.Num())

    D_OnReset.AddDynamic(this, &ACustomGameMode::ResetGameMode);
}



void ACustomGameMode::Tick(float DeltaSeconds)
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

void ACustomGameMode::StartGameTimer()
{
    GameStartTime = GetWorld()->GetUnpausedTimeSeconds();
    
}

void ACustomGameMode::ResetGameMode()
{

    gs->gameTimer = 0;

    //reset ability collection
    gs->hasXray = false;
    gs->hasWallGrip = false;
    gs->hasTeleport = false;
    gs->hasInvisibility = false;
    //make sure that invisibility is reset beyond just collection
    gs->bPlayerIsInvisible = false;
    gs->CurrentInvisCharge = 0;

    //int32 NumSpawnedCollectibles = SpawnedCollectiblesMap.Num();
    //LOG("size of array = %d", NumSpawnedCollectibles)

    //destroy each spawned powerup and remove it from the TMap
    for ( const auto& Pair : SpawnedCollectiblesMap) {
        LOG("PING")
        AActor* PowerUpActor = Pair.Value;
        PowerUpActor->Destroy();
        SpawnedCollectiblesMap.Remove(Pair.Key);
    }

    //NumSpawnedCollectibles = SpawnedCollectiblesMap.Num();
    //LOG("size of array = %d", NumSpawnedCollectibles)

    randomizePowerups();
        
    PlaceCollectibleArray();

    StartGameTimer();
}

void ACustomGameMode::PlaceCollectibleArray()
{
    int i = 0;
    for (EPowerUp OrderedPowerUp : gs->EA_PowerupOrder) {//FUTURE CLEANUP: do all this in helper functions rather than several messy case labels
        switch (OrderedPowerUp) {
        default:
        case(EPowerUp::PE_XRay):
        {
            //SpawnedCollectibles.Add(GetWorld()->SpawnActor<AActor>(XRayCollectible, PowerupSpawnLocations[i]->GetActorLocation(), FRotator(0, 0, 0)));

            AActor* PowerupActor = GetWorld()->SpawnActor<AActor>(XRayCollectible, PowerupSpawnLocations[i]->GetActorLocation(), FRotator(0, 0, 0));

            UXRayVision* Component = PowerupActor->FindComponentByClass<UXRayVision>();
            if (Component)
            {
                EPowerUp Key = EPowerUp::PE_XRay; // Use an appropriate method from your component to get the key
                SpawnedCollectiblesMap.Add(Key, PowerupActor);
            }

            //LOG("spawned powerup: %s", &LastSpawnedPowerup->GetName())
            //SpawnedCollectibles.Add(LastSpawnedPowerup);
            //if we wanted to access it later, we'd want to set a separate AActor*, and then cast this into that variable
            // eg XRayInteractable* exampleActor = Cast<XRayInteractable*>(GetWrold....)
            LOG("spawn an xray at %f %f ", PowerupSpawnLocations[i]->GetActorLocation().X, PowerupSpawnLocations[i]->GetActorLocation().Y)
        }
        break;
        case(EPowerUp::PE_Invisibility):
        {

            //SpawnedCollectibles.Add(GetWorld()->SpawnActor<AActor>(XRayCollectible, PowerupSpawnLocations[i]->GetActorLocation(), FRotator(0, 0, 0)));

            AActor* PowerupActor = GetWorld()->SpawnActor<AActor>(InvisibilityCollectible, PowerupSpawnLocations[i]->GetActorLocation(), FRotator(0, 0, 0));

            UInvisibilityPowerup* Component = PowerupActor->FindComponentByClass<UInvisibilityPowerup>();
            if (Component)
            {
                EPowerUp Key = EPowerUp::PE_Invisibility; // Use an appropriate method from your component to get the key
                SpawnedCollectiblesMap.Add(Key, PowerupActor);
            }

            //SpawnedCollectibles.Add(GetWorld()->SpawnActor<AActor>(InvisibilityCollectible, PowerupSpawnLocations[i]->GetActorLocation(), FRotator(0, 0, 0)));
            //SpawnedCollectibles.Add(LastSpawnedPowerup);
            LOG("spawn INVISIBILITY")
        }
        break;
        case(EPowerUp::PE_Teleport):
            LOG("spawn TELEPORT")
                break;
        case(EPowerUp::PE_Movement):
            LOG("spawn PE_Movement")
                break;
        }
        i++;
    }
}

void ACustomGameMode::CollectXRay()
{
    WARN("collect x ray method called from gamemode");
    gs->hasXray = true;

    SpawnedCollectiblesMap.FindAndRemoveChecked(EPowerUp::PE_XRay);

    //AActor* xraycol = SpawnedCollectibles.Find(UXRayVision);

    OnCollectedXray.Broadcast();

    //when implementing xray we're going to want to iterate over our list of fake walls - stored by way of getallactorsof class in beginPlay(), and call their toggleXray function
}

void ACustomGameMode::CollectInvisibility()
{
    SpawnedCollectiblesMap.FindAndRemoveChecked(EPowerUp::PE_Invisibility);
    WARN("player collected invisibility -gm");
    //gs->CurrentInvisCharge = InvisMaxCharge;
    gs->hasInvisibility = true;
}

void ACustomGameMode::ToggleInvisibility()
{
    if (gs->hasInvisibility) {

        if (gs->bPlayerIsInvisible) {
            gs->bPlayerIsInvisible = false; 
            UGameplayStatics::PlaySound2D(GetWorld(), SW_InvisDeactivate);

        }
        else {
            gs->bPlayerIsInvisible = true;
            UGameplayStatics::PlaySound2D(GetWorld(), SW_InvisActivate);

        }
    }
    else {
        WARN("You do not yet have that ability");
    }
}


void ACustomGameMode::randomizePowerups()
{
    TArray<EPowerUp> RandomizedArray;
    int powerupNumber = gs->EA_PowerupOrder.Num() ;
    for (int i = 0; i < powerupNumber ; i++) {
        //WARN("array number %d and we stepped up to %d ", powerupNumber, i)
        int rand = FMath::RandRange(0, powerupNumber-i-1 );//generate a random number from the number of loops we've had up 
        RandomizedArray.Add(gs->EA_PowerupOrder[rand]);
        gs->EA_PowerupOrder.RemoveAt(rand);

       

        //gs->EA_PowerupOrder

        
    }
    gs->EA_PowerupOrder = RandomizedArray;
}


//returns true if any changes are made to the charge
void ACustomGameMode::updateInvisCharge()
{

    if (gs->hasInvisibility) {

        //LOG("CurrentCharge: %f", gs->CurrentInvisCharge)
        bool bLocalPlayerIsInvisible = gs->bPlayerIsInvisible;
        if (bLocalPlayerIsInvisible) {
            if (gs->CurrentInvisCharge == 0) {
                return ;
            }
            else  if (gs->CurrentInvisCharge < 0) {
                gs->CurrentInvisCharge = 0;
                return ;
            }
            else if (gs->CurrentInvisCharge > 0) {

                gs->CurrentInvisCharge -= InvisDecrement/invis_precision;
                return ;
            }
        } else {
            if (gs->CurrentInvisCharge == InvisMaxCharge) {
                return ;
            }
            else  if (gs->CurrentInvisCharge > InvisMaxCharge) {
                gs->CurrentInvisCharge = InvisMaxCharge;
                return ;
            }
            else if (gs->CurrentInvisCharge < InvisMaxCharge) {
                gs->CurrentInvisCharge += InvisIncrement/invis_precision;
                return ;
            }
        }

    }
    return ;
}

