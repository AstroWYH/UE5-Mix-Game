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
	// ͳһ����PersistantUI
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

	// ����־�UI��List������PIE������Ϸerror���ŵ�UISubsystemBaseȥ��
	// IMixUIPersistantInterface::GetUIPersistantList().Empty();
}