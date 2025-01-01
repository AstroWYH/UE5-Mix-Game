// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "UObject/Object.h"
#include "MixAssetManager.generated.h"

class UMixAbilityAsset;
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

	const UMixAbilityAsset& GetAsset_Ability()
	{
		return GetOrLoadAssetData<UMixAbilityAsset>(AbilityAsset);
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

	UPROPERTY(EditDefaultsOnly, Category = Ability)
	TSoftObjectPtr<UMixAbilityAsset> AbilityAsset;

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

	// TODO: 艾希的内容，需要写到cpp吗
	UPROPERTY(EditDefaultsOnly, Category = "Skill|Ashe|Montage")
	FSoftObjectPath Skill_Ashe_Montage_Q;
	UPROPERTY(EditDefaultsOnly, Category = "Skill|Ashe|Montage")
	FSoftObjectPath Skill_Ashe_Montage_W;
	UPROPERTY(EditDefaultsOnly, Category = "Skill|Ashe|Montage")
	FSoftObjectPath Skill_Ashe_Montage_E;
	UPROPERTY(EditDefaultsOnly, Category = "Skill|Ashe|Montage")
	FSoftObjectPath Skill_Ashe_Montage_R;

	UPROPERTY(EditDefaultsOnly, Category = "Skill|Ashe|BP")
	TSubclassOf<AActor> Skill_Ashe_BP_Q;
	UPROPERTY(EditDefaultsOnly, Category = "Skill|Ashe|BP")
	TSubclassOf<AActor> Skill_Ashe_BP_Q_Ext;
	UPROPERTY(EditDefaultsOnly, Category = "Skill|Ashe|BP")
	TSubclassOf<AActor> Skill_Ashe_BP_W;
	UPROPERTY(EditDefaultsOnly, Category = "Skill|Ashe|BP")
	TSubclassOf<AActor> Skill_Ashe_BP_E;
	UPROPERTY(EditDefaultsOnly, Category = "Skill|Ashe|BP")
	TSubclassOf<AActor> Skill_Ashe_BP_R;

	UPROPERTY(EditDefaultsOnly, Category = "NormalAmmo|Ashe|BP")
	TSubclassOf<AActor> NormalAmmo_Ashe_BP;

	// 技能BP_Ability_Hero_Key
	UPROPERTY(EditDefaultsOnly, Category = "Hero|Ability|Ashe|Q")
	TSubclassOf<AMixAbilityBase> HeroAbilityAsheQ;
	UPROPERTY(EditDefaultsOnly, Category = "Hero|Ability|Ashe|Q")
	TSubclassOf<AMixAbilityBase> HeroAbilityAsheW;
	UPROPERTY(EditDefaultsOnly, Category = "Hero|Ability|Ashe|Q")
	TSubclassOf<AMixAbilityBase> HeroAbilityAsheE;
	UPROPERTY(EditDefaultsOnly, Category = "Hero|Ability|Ashe|Q")
	TSubclassOf<AMixAbilityBase> HeroAbilityAsheR;

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
