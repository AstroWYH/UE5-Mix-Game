// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI/MixUIPersistantInterface.h"
#include "UI/MixUISubsystemBase.h"
#include "MixUIBarsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMixUIBarsSubsystem : public UMixUISubsystemBase, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

public:
	virtual void OnHeroSpawned() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual bool IsTickable() const override { return !IsTemplate(); }

	virtual TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(UMixUIBarsSubsystem, STATGROUP_Tickables);
	}

public:
	virtual void CreateUI() override;

	virtual void BindUIEvent() override;

private:
	// void OnSpawnPlayActor();

	UFUNCTION()
	void UpdateUIBars(int32 DamageVal, int32 CurHealthVal, int32 MaxHealthVal);

private:
	UPROPERTY()
	TObjectPtr<class UUserWidget> BarsContainerUI;

	UPROPERTY()
	TObjectPtr<class UProgressBar> HealthProgress;
};