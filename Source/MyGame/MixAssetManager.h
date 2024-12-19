// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "UObject/Object.h"
#include "MixAssetManager.generated.h"

class UPrimaryDataAsset;
class UMixWidgetComponentAsset;
/**
 * 
 */
UCLASS()
class MYGAME_API UMixAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	const UMixWidgetComponentAsset& GetHeadUIPath()
	{
		return GetOrLoadTypedGameData<UMixWidgetComponentAsset>(HeadUIPath);
	}

public:
	static UMixAssetManager& Get();

private:
	UPROPERTY()
	TSoftObjectPtr<UMixWidgetComponentAsset> HeadUIPath;

private:
	template <typename GameDataClass>
	const GameDataClass& GetOrLoadTypedGameData(const TSoftObjectPtr<GameDataClass>& DataPath)
	{
		if (TObjectPtr<UPrimaryDataAsset> const* pResult = AssetDataMap.Find(GameDataClass::StaticClass()))
		{
			return *CastChecked<GameDataClass>(*pResult);
		}

		// Does a blocking load if needed
		return *CastChecked<const GameDataClass>(LoadAssetDataOfClass(GameDataClass::StaticClass(), DataPath, GameDataClass::StaticClass()->GetFName()));
	}

	UPrimaryDataAsset* LoadAssetDataOfClass(TSubclassOf<UPrimaryDataAsset> DataClass, const TSoftObjectPtr<UPrimaryDataAsset>& DataClassPath, FPrimaryAssetType PrimaryAssetType);

	UPROPERTY(Transient)
	TMap<TObjectPtr<UClass>, TObjectPtr<UPrimaryDataAsset>> AssetDataMap;
};
