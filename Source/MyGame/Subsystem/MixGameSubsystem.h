// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MixGameSubsystem.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MYGAME_API UMixGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void OnHeroSpawned();
};
