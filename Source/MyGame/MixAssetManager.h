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
UCLASS(BlueprintType, Blueprintable)
class MYGAME_API UMixAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	const UMixWidgetComponentAsset& GetHeadUIPath()
	{
		return GetOrLoadAssetData<UMixWidgetComponentAsset>(HeadUIPath);
	}

public:
	static UMixAssetManager& Get();

public:
	// 方法1：直接用TObjectPtr，优点是简单，不用调下面复杂的一堆逻辑；缺点是不能懒加载，上来就需要加载，虽然目前都是UClass，但保不齐有其他资源
	// UPrimaryDataAsset都可以用TObjectPtr，启动加载，毕竟里面仅是UClass
	// UPROPERTY(EditDefaultsOnly, Category = UMixAssetManager)
	// TObjectPtr<UMixWidgetComponentAsset> HeadUIPath;

	// 方法2：用TSoftObjectPtr懒加载，需要的时候加载，并存到AssetDataMap
	UPROPERTY(EditDefaultsOnly, Category = UMixAssetManager)
	TSoftObjectPtr<UMixWidgetComponentAsset> HeadUIPath;

private:
	template <typename AssetClass>
	const AssetClass& GetOrLoadAssetData(const TSoftObjectPtr<AssetClass>& DataPath)
	{
		if (TObjectPtr<UPrimaryDataAsset> const* pResult = AssetDataMap.Find(AssetClass::StaticClass()))
		{
			return *CastChecked<AssetClass>(*pResult);
		}

		// Does a blocking load if needed
		return *CastChecked<const AssetClass>(LoadAssetDataOfClass(AssetClass::StaticClass(), DataPath, AssetClass::StaticClass()->GetFName()));
	}

	UPrimaryDataAsset* LoadAssetDataOfClass(TSubclassOf<UPrimaryDataAsset> DataClass, const TSoftObjectPtr<UPrimaryDataAsset>& DataClassPath, FPrimaryAssetType PrimaryAssetType);

	UPROPERTY(Transient)
	TMap<TObjectPtr<UClass>, TObjectPtr<UPrimaryDataAsset>> AssetDataMap;
};
