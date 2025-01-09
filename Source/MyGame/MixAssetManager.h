// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/AssetManager.h"
#include "UObject/Object.h"
#include "Engine/DataTable.h"

#include "MixAssetManager.generated.h"

class UMixAbilityAsset;
class UPrimaryDataAsset;
class UMixWidgetComponentAsset;

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAssetLoaded, UObject*, LoadedAsset);

USTRUCT(BlueprintType)
struct FCreatureModelInfo
{
	GENERATED_BODY()

	// 蒙太奇可以用FSoftObjectPath
	UPROPERTY(EditDefaultsOnly, Category = "Creature")
	FSoftObjectPath AttackMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Creature")
	TSubclassOf<AActor> Ammo; // 只有远程用
	UPROPERTY(EditDefaultsOnly, Category = "Creature")
	TSubclassOf<AActor> Class;
	UPROPERTY(EditDefaultsOnly, Category = "Creature")
	TSubclassOf<AActor> SpawnPoint;
	UPROPERTY(EditDefaultsOnly, Category = "Creature")
	TSubclassOf<AActor> PathPoint; // 只有小兵在用
};

USTRUCT(BlueprintType)
struct FHeroModelInfo : public FCreatureModelInfo
{
	GENERATED_BODY()

	// USkeletalMesh用FSoftObjectPath会报错，在ResolveObjectHandleNoRead，不知道为什么；就用TSoftObjectPtr同步加载，官方也这样
	UPROPERTY(EditDefaultsOnly, Category = "Creature|Hero")
	TSoftObjectPtr<USkeletalMesh> Mesh;
	UPROPERTY(EditDefaultsOnly, Category = "Creature|Hero")
	TSubclassOf<UAnimInstance> Anim;
	UPROPERTY(EditDefaultsOnly, Category = "Creature|Hero")
	TSubclassOf<AActor> HeroController;
};

UCLASS(BlueprintType, Blueprintable)
class MYGAME_API UMixAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static UMixAssetManager& Get();

	UFUNCTION(BlueprintCallable)
	static UMixAssetManager* GetPtr();
	
public:
	// 方法1：直接用TObjectPtr，优点是简单，不用调下面复杂的一堆逻辑；
	// 缺点是不能懒加载，上来就需要加载，虽然目前都是UClass，但保不齐有其他资源
	// UPrimaryDataAsset都可以用TObjectPtr，启动加载，毕竟里面仅是UClass
	// UPROPERTY(EditDefaultsOnly, Category = UMixAssetManager)
	// TObjectPtr<UMixWidgetComponentAsset> HeadUIAsset;

	// 这两个作为DA，就不往结构体里移动了，作为示例展示
	UPROPERTY(EditDefaultsOnly, Category = "Creature|Hero|Ability")
	TSoftObjectPtr<UMixAbilityAsset> AbilityAsset;
	// 方法2：用TSoftObjectPtr懒加载，需要的时候加载，并存到AssetDataMap
	// 以资产DA的形式存在，创建比较麻烦，但是使用更规范，也可以懒加载
	// UPROPERTY(EditDefaultsOnly, Category = "Creature|HeadUI")
	// TSoftObjectPtr<UMixWidgetComponentAsset> HeadUIAsset;

	UPROPERTY(EditDefaultsOnly, Category = "Creature|HeadUI")
	TSubclassOf<UUserWidget> HeadUIWidget;

	// 方式6: 可以用DA的形式，但需要写一个DA子类，也可以直接在这写Map
	UPROPERTY(EditDefaultsOnly, Category = "Creature")
	TMap<FGameplayTag, FHeroModelInfo> HeroModelInfo;
	UPROPERTY(EditDefaultsOnly, Category = "Creature")
	TMap<FGameplayTag, FCreatureModelInfo> CreatureModelInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Creature|Attribute")
	TSoftObjectPtr<UDataTable> AttributeData; // 并非一个Creature对应一张表，因此不移动到ModelInfo
	UPROPERTY(EditDefaultsOnly, Category = "Creature|Hero|Attribute")
	TSoftObjectPtr<UDataTable> HeroAttributeData;

	UPROPERTY(EditDefaultsOnly, Category = "Creature|Controller")
	TSubclassOf<AActor> HostHeroController;

public:
	// 方式4：同步加载TSoftObjectPtr，凡是LoadObject的，都能这样加载，因为里面也会LoadObject
	template <typename AssetClass>
	UFUNCTION(BlueprintCallable)
	AssetClass* GetAssetSync(const TSoftObjectPtr<AssetClass>& SoftPtr)
	{
		AssetClass* Asset = SoftPtr.LoadSynchronous();
		return Asset;
	}

	// 方式5：异步加载，尝试使用FSoftObjectPath，看起来FSoftObjectPath不需要像TSoftObjectPtr提供类型
	void GetAssetASync(const FSoftObjectPath& SoftObjectPath, const FStreamableDelegate& OnLoadedDelegate);

public:
	template <typename AssetClass>
	const AssetClass& GetOrLoadAssetData(const TSoftObjectPtr<AssetClass>& DataPath)
	{
		if (TObjectPtr<UPrimaryDataAsset> const* pResult = AssetDataMap.Find(AssetClass::StaticClass()))
		{
			return *CastChecked<AssetClass>(*pResult);
		}

		return *CastChecked<const AssetClass>(LoadAssetDataOfClass(AssetClass::StaticClass(), DataPath, AssetClass::StaticClass()->GetFName()));
	}
	
private:
	UPrimaryDataAsset* LoadAssetDataOfClass(TSubclassOf<UPrimaryDataAsset> DataClass, const TSoftObjectPtr<UPrimaryDataAsset>& DataClassPath, FPrimaryAssetType PrimaryAssetType);

	UPROPERTY(Transient)
	TMap<TObjectPtr<UClass>, TObjectPtr<UPrimaryDataAsset>> AssetDataMap;

};
