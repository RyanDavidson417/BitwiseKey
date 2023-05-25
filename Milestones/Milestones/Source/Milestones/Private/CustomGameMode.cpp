// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameMode.h"
#include "CustomGameState.h"
#include "PlayerCharacter.h"
#include "Milestones/Milestones.h"
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

//C:\Users\ryand\LocDocuments\Indie games\Unreal\gp2 repo\Milestones\Milestones\Source\Milestones\Private\CustomGameMode.cpp