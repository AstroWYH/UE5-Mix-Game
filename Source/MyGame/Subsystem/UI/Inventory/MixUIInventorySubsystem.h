// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI/MixUIPersistantInterface.h"
#include "MixUIInventorySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMixUIInventorySubsystem : public UGameInstanceSubsystem, public IMixUIPersistantInterface
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	virtual void CreateUI() override;

public:
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