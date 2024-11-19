// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MixUISubsystem.generated.h"

/**
 * 该类暂时不起作用
 */
UCLASS()
class MYGAME_API UMixUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void Initialize(FSubsystemCollectionBase& Collection) override;

	void Deinitialize() override;

public:
	void CreateInventoryUI();

	void CreateTestBtnUI();

	UFUNCTION()
	void UpdateInventory();

private:
	const TCHAR* BpInventoryClassPath = TEXT(
		"/Script/UMGEditor.WidgetBlueprint'/Game/MixGame/UI/Inventory/WB_Inventory.WB_Inventory_C'");

	const TCHAR* BpItemClassPath = TEXT(
		"/Script/UMGEditor.WidgetBlueprint'/Game/MixGame/UI/Inventory/WB_InventoryItem.WB_InventoryItem_C'");

	UClass* BpInventoryClass = nullptr;

	UClass* BpItemClass = nullptr;

public:
	UPROPERTY()
	TObjectPtr<class UMixInventoryWidget> InventoryUI;

	UPROPERTY()
	TArray<TObjectPtr<class UMixItemWidget>> ItemUIPool;
};