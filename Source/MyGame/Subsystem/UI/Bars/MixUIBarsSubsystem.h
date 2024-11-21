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
class MYGAME_API UMixUIBarsSubsystem : public UMixUISubsystemBase
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

public:
	virtual void CreatePersistantUI() override;

public:
	virtual void LoadUIClass() override;

	virtual void BindUpdateUIEvent() override;

public:
	void OnTakeDamage(int32 LocalUserNum);

	UFUNCTION()
	void UpdateUIBars(int32 DamageVal);

private:
	UPROPERTY()
	UClass* BpBarContainerClass = nullptr;

	UPROPERTY()
	UClass* BpHealthClass = nullptr;

	UPROPERTY()
	UClass* BpMagicClass = nullptr;

private:
	UPROPERTY()
	TObjectPtr<class UMixBarsContainerWidget> BarsContainerUI;
};