#include "MixUIMgr.h"

#include "Game/MixWorldSettings.h"
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
	AMixWorldSettings* WorldSettings = Cast<AMixWorldSettings>(GetWorld()->GetWorldSettings());
	if (!ensure(WorldSettings)) return;

	// DA类就直接这样加载是最合理且方便的
	UIAssets = WorldSettings->UIAssets;

	// 不要用蓝图类来装配置数据，容易加载出nullptr
	// UIAssets = Cast<UMixUIAsset>(StaticLoadObject(UMixUIAsset::StaticClass(), nullptr, *UIAssetsClass->GetPathName()));
	// UIAssets = Cast<UMixUIAsset>(StaticLoadObject(UMixUIAsset::StaticClass(), nullptr, TEXT("/Script/MyGame.MixUIAsset'/Game/MixGame/UI/DA_UIAssets.DA_UIAssets'")));
}

TSubclassOf<UUserWidget> UMixUIMgr::GetUIClass(FName Module, FName Name)
{
	const TMap<FName, FUIClassArray>& AllUIAssets = UIAssets->GetAllUIAssets();
	if (!ensure(AllUIAssets.Contains(Module))) return TSubclassOf<UUserWidget>();

	const TMap<FName, TSubclassOf<UUserWidget>>& ModuleClasses = AllUIAssets[Module].UIClasses;
	if (!ensure(ModuleClasses.Contains(Name))) return TSubclassOf<UUserWidget>();

	return ModuleClasses[Name];
}

void UMixUIMgr::PostInit()
{
	CreateMainLayout();

	// 统一创建PersistantUI
	InitAllPersistantUI();
}

void UMixUIMgr::CreateMainLayout()
{
	UUserWidget* MainLayout = Cast<UUserWidget>(UUserWidget::CreateWidgetInstance(*GetGameInstance(), GetUIClass(GetClass()->GetFName(), "MainLayout"), "MainLayout"));

	GetUIBPData(MainLayout, MainLayoutSlots);
	MainLayout->AddToViewport();
}

void UMixUIMgr::InitAllPersistantUI()
{
	const auto& UIPersistantList = IMixUIPersistantInterface::GetUIPersistantList();
	for (const auto& UIPersistantUISub : UIPersistantList)
	{
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
}

// 配置在DefaultGame.ini的方式
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
