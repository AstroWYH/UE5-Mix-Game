// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyGameGameMode.h"
#include "Character/Character/Host/MixHost.h"
#include "UObject/ConstructorHelpers.h"

AMyGameGameMode::AMyGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
