#include "Subsystem/UI/MixUISubsystem.h"
#include "UI/MixUIPersistantInterface.h"

void UMixUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	CreatePersistantUI();
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
}