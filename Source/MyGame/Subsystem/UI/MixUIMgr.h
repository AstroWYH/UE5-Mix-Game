// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MixUIMgr.generated.h"

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

public:
	void InitAllPersistantUI();

	void GetUIBPData(UUserWidget* Widget, TMap<FName, UObject*>& BPVarDataMap);

private:
	TSharedPtr<const TMap<FName, FUIClassArray>> UIAssetMap;

	UPROPERTY()
	const UMixUIAsset* UIAssets;

public:
	TSharedPtr<const TMap<FName, FUIClassArray>> GetAllUIAssets() const
	{
		return UIAssetMap;
	}
};