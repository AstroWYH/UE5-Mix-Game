// Fill out your copyright notice in the Description page of Project Settings.


#include "MixGameInstance.h"

int32 UMixGameInstance::AddLocalPlayer(ULocalPlayer* NewPlayer, FPlatformUserId UserId)
{
	int32 InsertIndex = Super::AddLocalPlayer(NewPlayer, UserId);
	OnLocalPlayerAdd.Broadcast();

	return InsertIndex;
}
