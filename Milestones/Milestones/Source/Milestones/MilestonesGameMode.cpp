// Copyright Epic Games, Inc. All Rights Reserved.

#include "MilestonesGameMode.h"
#include "MilestonesCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMilestonesGameMode::AMilestonesGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
