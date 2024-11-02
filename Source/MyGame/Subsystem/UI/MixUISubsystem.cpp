
#include "Subsystem/UI/MixUISubsystem.h"
#include "Subsystem/Inventory/MixInventorySubsystem.h"

void UMixUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Collection.InitializeDependency(UMixInventorySubsystem::StaticClass());
	GetGameInstance()->GetSubsystem<UMixInventorySubsystem>()->OnInventoryUpdated.AddDynamic(this, &ThisClass::Test);
	BpInitialize();
}

void UMixUISubsystem::Deinitialize()
{
	Super::Deinitialize();

	BpDeInitialize();
}

void UMixUISubsystem::Test()
{
	UE_LOG(LogTemp, Warning, TEXT("Mix Test"));
}
