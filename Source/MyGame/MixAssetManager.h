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
	const UMixWidgetComponentAsset& GetAsset_HeadUI()
	{
		return GetOrLoadAssetData<UMixWidgetComponentAsset>(HeadUIAsset);
	}

public:
	static UMixAssetManager& Get();

public:
	// 方法1：直接用TObjectPtr，优点是简单，不用调下面复杂的一堆逻辑；缺点是不能懒加载，上来就需要加载，虽然目前都是UClass，但保不齐有其他资源
	// UPrimaryDataAsset都可以用TObjectPtr，启动加载，毕竟里面仅是UClass
	// UPROPERTY(EditDefaultsOnly, Category = UMixAssetManager)
	// TObjectPtr<UMixWidgetComponentAsset> HeadUIAsset;

	// 方法2：用TSoftObjectPtr懒加载，需要的时候加载，并存到AssetDataMap
	// 以资产DA的形式存在，创建比较麻烦，但是使用更规范，也可以懒加载
	UPROPERTY(EditDefaultsOnly, Category = HeadUI)
	TSoftObjectPtr<UMixWidgetComponentAsset> HeadUIAsset;

	// 方式3
	// 以UClass的形式存在，方便，用来写这个PathClass；缺点是在BP_AssetManager里越放越多
	UPROPERTY(EditDefaultsOnly, Category = Point)
	TSubclassOf<AActor> HeroSpawnPointClass;
	UPROPERTY(EditDefaultsOnly, Category = Point)
	TSubclassOf<AActor> BatmanSpawnPointClass;
	UPROPERTY(EditDefaultsOnly, Category = Point)
	TSubclassOf<AActor> BatmanPathPointClass;

	UPROPERTY(EditDefaultsOnly, Category = Creature)
	TSubclassOf<AActor> HeroClass;
	UPROPERTY(EditDefaultsOnly, Category = Creature)
	TSubclassOf<AActor> BatmanClass;
	UPROPERTY(EditDefaultsOnly, Category = Controller)
	TSubclassOf<AActor> HeroController;

	UPROPERTY(EditDefaultsOnly, Category = "Montage|Skill|Ashe")
	FSoftObjectPath Skill_Ashe_Q;
	UPROPERTY(EditDefaultsOnly, Category = "Montage|Skill|Ashe")
	FSoftObjectPath Skill_Ashe_W;
	UPROPERTY(EditDefaultsOnly, Category = "Montage|Skill|Ashe")
	FSoftObjectPath Skill_Ashe_E;
	UPROPERTY(EditDefaultsOnly, Category = "Montage|Skill|Ashe")
	FSoftObjectPath Skill_Ashe_R;

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
