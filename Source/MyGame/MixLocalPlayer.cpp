// Fill out your copyright notice in the Description page of Project Settings.

#include "MixLocalPlayer.h"
#include "MixGameInstance.h"

bool UMixLocalPlayer::SpawnPlayActor(const FString& URL, FString& OutError, UWorld* InWorld)
{
	const bool bResult = Super::SpawnPlayActor(URL, OutError, InWorld);
	OnSpawnPlayActor.Broadcast();

	UMixGameInstance* GameInstance = Cast<UMixGameInstance>(GetGameInstance());
	GameInstance->OnSpawnPlayActor.Broadcast();

	return bResult;
}
