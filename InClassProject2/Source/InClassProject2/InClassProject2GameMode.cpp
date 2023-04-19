// Copyright Epic Games, Inc. All Rights Reserved.

#include "InClassProject2GameMode.h"
#include "InClassProject2Character.h"
#include "UObject/ConstructorHelpers.h"

AInClassProject2GameMode::AInClassProject2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
