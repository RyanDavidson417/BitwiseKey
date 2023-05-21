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
    WARN("COLLECT METHOD CALLED FROM GAMEMODE");
    gs->hasXray;
}

//C:\Users\ryand\LocDocuments\Indie games\Unreal\gp2 repo\Milestones\Milestones\Source\Milestones\Private\CustomGameMode.cpp