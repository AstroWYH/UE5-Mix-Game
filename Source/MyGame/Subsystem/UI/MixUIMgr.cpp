#include "MixUIMgr.h"

#include "MixUIAsset.h"
#include "MixWorldSettings.h"
#include "Engine/AssetManager.h"
#include "UI/MixUIPersistantInterface.h"
#include "Blueprint\UserWidget.h"

void UMixUIMgr::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// 加载所有的持久性UI资源
	LoadUIAssets();

	GetWorld()->GetTimerManager().SetTimerForNextTick(
		FTimerDelegate::CreateUObject(this, &UMixUIMgr::PostInit));
}

void UMixUIMgr::LoadUIAssets()
{
	// UAssetManager& AssetManager = UAssetManager::Get();
	// FPrimaryAssetType UIAssetType = UMixUIAsset::StaticClass()->GetFName();
	// TSharedPtr<FStreamableHandle> Handle = AssetManager.LoadPrimaryAssetsWithType(UIAssetType);
	// if (ensure(Handle.IsValid()))
	// {
	// 	Handle->WaitUntilComplete();
	// }
	//
	// TArray<UObject*> LoadUIAssets;
	// AssetManager.GetPrimaryAssetObjectList(UIAssetType, LoadUIAssets);
	// if (!ensure(LoadUIAssets.Num() == 1)) return;
	//
	// UMixUIAsset* UIAssets = Cast<UMixUIAsset>(LoadUIAssets[0]);
	// if (!ensure(UIAssets)) return;
	//
	// UIAssetMap = MakeShareable<const TMap<FName, FUIClassArray>>(&(UIAssets->GetAllUIAsset()));

	AMixWorldSettings* WorldSettings = Cast<AMixWorldSettings>(GetWorld()->GetWorldSettings());
	if (!ensure(WorldSettings)) return;
	
	TSubclassOf<UMixUIAsset> UIAssetsClass = WorldSettings->GetMixUIAssets();
	// const UMixUIAsset* UIAssets = Cast<UMixUIAsset>(StaticLoadObject(UMixUIAsset::StaticClass(), nullptr, *UIAssetsClass->GetPathName()));
	UIAssets = LoadObject<UMixUIAsset>(nullptr, *UIAssetsClass->GetPathName());
	UIAssetMap = MakeShareable<const TMap<FName, FUIClassArray>>(&(UIAssets->GetAllUIAsset()));
}

// UClass* UMixUIMgr::LoadUIClass(const FString& ModulePath, const FString& BlueprintName)
// {
// 	FString GameBasePath;
// 	GConfig->GetString(TEXT("/Script/Engine.GameSettings"), TEXT("GameBasePath"), GameBasePath, GGameIni);
// 	FString FullPath = FString::Printf(
// 		TEXT("/Script/UMGEditor.WidgetBlueprint'%s%s%s'"), *GameBasePath, *ModulePath, *BlueprintName);
//
// 	UClass* LoadedClass = LoadClass<UObject>(nullptr, *FullPath);
// 	if (!ensure(LoadedClass)) return nullptr;
//
// 	return LoadedClass;
// }

void UMixUIMgr::PostInit()
{
	// 统一创建PersistantUI
	InitAllPersistantUI();
}

void UMixUIMgr::InitAllPersistantUI()
{
	const auto& UIPersistantList = IMixUIPersistantInterface::GetUIPersistantList();
	for (const auto& UIPersistantUISub : UIPersistantList)
	{
		UIPersistantUISub->LoadUIClass();
		UIPersistantUISub->CreateUI();
		UIPersistantUISub->BindUIEvent();
	}
}

void UMixUIMgr::GetUIBPData(UUserWidget* Widget, TMap<FName, UObject*>& BPVarDataMap)
{
	if (!ensure(Widget)) return;

	UClass* WidgetClass = Widget->GetClass();
	for (TFieldIterator<FProperty> PropIt(WidgetClass); PropIt; ++PropIt)
	{
		FProperty* Property = *PropIt;
		if (Property->HasAnyPropertyFlags(CPF_ExportObject))
		{
			if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
			{
				if (ObjectProperty->PropertyClass->IsChildOf(UWidget::StaticClass()))
				{
					FName WidgetName = Property->GetFName();
					UObject* WidgetInstance = ObjectProperty->GetObjectPropertyValue_InContainer(Widget);

					if (WidgetInstance)
					{
						BPVarDataMap.Add(WidgetName, WidgetInstance);
					}
				}
			}
		}
	}
}

void UMixUIMgr::Deinitialize()
{
	Super::Deinitialize();

	// 清理持久UI的List，否则PIE重启游戏error，放到UISubsystemBase去做
	// IMixUIPersistantInterface::GetUIPersistantList().Empty();
}
