
#include "Subsystem/UI/MixUISubsystem.h"
#include "Subsystem/Inventory/MixInventorySubsystem.h"

void UMixUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Collection.InitializeDependency(UMixInventorySubsystem::StaticClass());
	// GetGameInstance()->GetSubsystem<UMixInventorySubsystem>()->OnInventoryUpdated.AddDynamic(this, &ThisClass::UpdateInventory);
	BpInitialize();
}

void UMixUISubsystem::Deinitialize()
{
	Super::Deinitialize();

	BpDeInitialize();
}

/*
void UMixUISubsystem::UpdateInventory()
{
	UE_LOG(LogTemp, Warning, TEXT("Mix Test"));
}*/
