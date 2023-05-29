// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameMode.h"
#include "CustomGameState.h"
#include "PlayerCharacter.h"
#include "Math/UnrealMathUtility.h"
#include "Milestones/Milestones.h"
#include "Kismet/KismetArrayLibrary.h"
#include "CustomGameState.h"


ACustomGameMode::ACustomGameMode()
{

    /** initialize some of the defaults, blueprinting this will override it,
        notice the use of StaticClass to get the UClass class type properly */
    DefaultPawnClass = APlayerCharacter::StaticClass();
    GameStateClass = ACustomGameState::StaticClass();

}


void ACustomGameMode::BeginPlay()
{
    gs = GetWorld()->GetGameState<ACustomGameState>();
    randomizePowerups();

}

void ACustomGameMode::CollectXRay()
{
    WARN("collect x ray method called from gamemode");
    gs->hasXray = true;

    //when implementing xray we're going to want to iterate over our list of fake walls - stored by way of getallactorsof class in beginPlay(), and call their toggleXray function
}

void ACustomGameMode::CollectInvisibility()
{
    WARN("player collected invisibility -gm");

    gs->hasInvisibility = true;
}

void ACustomGameMode::ToggleInvisibility()
{
    if (gs->hasInvisibility) {

        if (gs->bPlayerIsInvisible) {
            gs->bPlayerIsInvisible = false; 

        }
        else {
            gs->bPlayerIsInvisible = true;

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

//C:\Users\ryand\LocDocuments\Indie games\Unreal\gp2 repo\Milestones\Milestones\Source\Milestones\Private\CustomGameMode.cpp