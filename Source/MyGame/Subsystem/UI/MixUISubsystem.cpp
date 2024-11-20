#include "Subsystem/UI/MixUISubsystem.h"
#include "UI/MixUIPersistantInterface.h"

void UMixUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// TODO: 需要PostInit
	GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUObject(this, &UMixUISubsystem::CreatePersistantUI));
}

UClass* UMixUISubsystem::LoadUIResource(const TCHAR* Path)
{
	UClass* BpUIClass = LoadObject<UClass>(nullptr, Path);
	if (!ensure(BpUIClass)) return nullptr;

	return BpUIClass;
}

void UMixUISubsystem::CreatePersistantUI()
{
	const auto& UIPersistantList = IMixUIPersistantInterface::GetUIPersistantList();
	for (const auto& UIPersistantUISub : UIPersistantList)
	{
		UIPersistantUISub->CreateUI();
	}
}

void UMixUISubsystem::Deinitialize()
{
	Super::Deinitialize();

	// 清理持久UI的List，否则PIE重启游戏error，放到每个UISubsystem去做
	// IMixUIPersistantInterface::GetUIPersistantList().Empty();
}