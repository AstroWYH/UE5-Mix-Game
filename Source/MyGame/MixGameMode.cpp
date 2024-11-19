// Fill out your copyright notice in the Description page of Project Settings.


#include "MixGameMode.h"

AMixGameMode::AMixGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Script/Engine.Blueprint'/Game/MixGame/Character/Host/HostCharacterBp.HostCharacterBp'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}