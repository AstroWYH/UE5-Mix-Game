// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MixLevelSubsystem.generated.h"

class AMixBatman;
class AMixHero;
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
	void GenerateHero();

	// TODO: 在Tick里周期生成
	void GenerateBatman();

	// 通过SpawnedHeros保证不被GC
	UPROPERTY()
	TArray<AMixHero*> SpawnedHeros;

	UPROPERTY()
	TArray<AMixBatman*> SpawnedBatmans;

	AMixHero* HostHero;

public:
	TArray<AMixHero*> GetSpawnedHeros() const
	{
		return SpawnedHeros;
	}

	AMixHero* GetHostHero() const
	{
		return HostHero;
	}
};