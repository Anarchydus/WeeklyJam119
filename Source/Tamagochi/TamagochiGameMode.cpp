// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TamagochiGameMode.h"
#include "TamagochiPlayerController.h"
#include "TamagochiCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATamagochiGameMode::ATamagochiGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATamagochiPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}