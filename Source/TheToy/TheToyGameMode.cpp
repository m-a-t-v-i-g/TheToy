// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheToyGameMode.h"
#include "TheToyCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheToyGameMode::ATheToyGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
