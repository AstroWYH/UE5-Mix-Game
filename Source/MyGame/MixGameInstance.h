// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MixGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMixGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual int32 AddLocalPlayer(ULocalPlayer* NewPlayer, FPlatformUserId UserId) override;

public:
	DECLARE_MULTICAST_DELEGATE(FOnLocalPlayerAdd);
	FOnLocalPlayerAdd OnLocalPlayerAdd;

	DECLARE_MULTICAST_DELEGATE(FOnSpawnPlayActor);
	FOnSpawnPlayActor OnSpawnPlayActor;	
	
};
