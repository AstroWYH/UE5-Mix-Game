// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/UI/MixUIAsset.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MixUIMgr.generated.h"

struct FUIClassArray;

UCLASS()
class MYGAME_API UMixUIMgr : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	void PostInit();

private:
	void LoadUIAssets();

	void CreateMainLayout();

public:
	void InitAllPersistantUI();

	void GetUIBPData(UUserWidget* Widget, TMap<FName, UObject*>& BPVarDataMap);

private:
	UPROPERTY()
	TObjectPtr<UMixUIAsset> UIAssets;

	UPROPERTY()
	TMap<FName, UObject*> MainLayoutSlots;

public:
	TMap<FName, UObject*> GetMainLayoutSlots() const
	{
		return MainLayoutSlots;
	}

	TSubclassOf<UUserWidget> GetUIClass(FName Module, FName Name);

};