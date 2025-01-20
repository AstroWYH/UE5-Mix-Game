// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MixLevelSubsystem.generated.h"

class AMixTower;
class AMixBatman;
class AMixHero;
struct FGameplayTag;
/**
 * 
 */
UCLASS()
class MYGAME_API UMixLevelSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

private:
	void GenerateHeros();

	// TODO: 在Tick里周期生成
	void GenerateBatmans();

	void GenerateTowers();
	
	AMixBatman* SpawnBatman(const AActor* SpawnPoint, const FGameplayTag& Type);

	AMixTower* SpawnTower(const AActor* SpawnPoint, const FGameplayTag& Type);

	// 通过SpawnedHeros保证不被GC
	UPROPERTY()
	TArray<AMixHero*> SpawnedHeros;

	UPROPERTY()
	TArray<AMixBatman*> SpawnedBatmans;

	UPROPERTY()
	TArray<AMixTower*> SpawnedTowers;

public:
	UFUNCTION(BlueprintCallable)
	TArray<AMixBatman*> GetSpawnedBatmans() const
	{
		return SpawnedBatmans;
	}

private:
	AMixHero* HostHero;

public:
	UFUNCTION(BlueprintCallable)
	TArray<AMixHero*> GetSpawnedHeros() const
	{
		return SpawnedHeros;
	}
	
	UFUNCTION(BlueprintCallable)
	AMixHero* GetHostHero() const
	{
		return HostHero;
	}
};