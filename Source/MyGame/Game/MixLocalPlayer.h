// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LocalPlayer.h"
#include "MixLocalPlayer.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMixLocalPlayer : public ULocalPlayer
{
	GENERATED_BODY()

public:
	virtual bool SpawnPlayActor(const FString& URL, FString& OutError, UWorld* InWorld) override;

public:
	DECLARE_MULTICAST_DELEGATE(FOnSpawnPlayActor);
	FOnSpawnPlayActor OnSpawnPlayActor;
};
