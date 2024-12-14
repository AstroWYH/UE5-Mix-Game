// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI/MixUIPersistantInterface.h"
#include "UI/MixUISubsystemBase.h"
#include "MixUIInventorySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMixUIInventorySubsystem : public UMixUISubsystemBase
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

public:
	virtual void CreatePersistantUI() override;

public:
	virtual void LoadUIClass() override;

	virtual void BindUIEvent() override;

public:
	UFUNCTION()
	void UpdateInventory();

private:
	UPROPERTY()
	TObjectPtr<class UMixInventoryWidget> InventoryUI;

	UPROPERTY()
	TArray<TObjectPtr<class UMixItemWidget>> ItemUIPool;

private:
	UPROPERTY()
	UClass* BpInventoryClass = nullptr;

	UPROPERTY()
	UClass* BpItemClass = nullptr;
};