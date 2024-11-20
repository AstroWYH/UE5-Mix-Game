// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MixLevelSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMixLevelSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

private:
	const TCHAR* BpSpawnPointPath = TEXT(
		"/Script/Engine.Blueprint'/Game/MixGame/Character/EnemyBatman/Point/EnemySpawnPoint.EnemySpawnPoint_C'");

	const TCHAR* BpBatmanClassPath = TEXT(
		"/Script/Engine.Blueprint'/Game/MixGame/Character/EnemyBatman/BatmanBp.BatmanBp_C'");
};