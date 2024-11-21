#include "MixUIMgrSubsystem.h"
#include "UI/MixUIPersistantInterface.h"

void UMixUIMgrSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GetWorld()->GetTimerManager().SetTimerForNextTick(
		FTimerDelegate::CreateUObject(this, &UMixUIMgrSubsystem::PostInit));
}

UClass* UMixUIMgrSubsystem::LoadUIClass(const FString& ModulePath, const FString& BlueprintName)
{
	FString GameBasePath;
	GConfig->GetString(TEXT("/Script/Engine.GameSettings"), TEXT("GameBasePath"), GameBasePath, GGameIni);
	FString FullPath = FString::Printf(
		TEXT("/Script/UMGEditor.WidgetBlueprint'%s%s%s'"), *GameBasePath, *ModulePath, *BlueprintName);

	UClass* LoadedClass = LoadClass<UObject>(nullptr, *FullPath);
	if (!ensure(LoadedClass)) return nullptr;

	return LoadedClass;
}

void UMixUIMgrSubsystem::PostInit()
{
	// 统一创建PersistantUI
	CreatePersistantUI();
}

void UMixUIMgrSubsystem::CreatePersistantUI()
{
	const auto& UIPersistantList = IMixUIPersistantInterface::GetUIPersistantList();
	for (const auto& UIPersistantUISub : UIPersistantList)
	{
		UIPersistantUISub->CreatePersistantUI();
	}
}

void UMixUIMgrSubsystem::Deinitialize()
{
	Super::Deinitialize();

	// 清理持久UI的List，否则PIE重启游戏error，放到UISubsystemBase去做
	// IMixUIPersistantInterface::GetUIPersistantList().Empty();
}