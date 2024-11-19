#include "Subsystem/UI/MixUISubsystem.h"
#include "Subsystem/Inventory/MixInventorySubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/UniformGridPanel.h"
#include "Inventory/MixInventoryItem.h"
#include "UI/Item/MixInventoryWidget.h"
#include "UI/Item/MixItemWidget.h"

void UMixUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	CreateInventoryUI();
	CreateTestBtnUI();
}

void UMixUISubsystem::CreateInventoryUI()
{
	UMixInventorySubsystem* InventorySubsystem = GetGameInstance()->GetSubsystem<UMixInventorySubsystem>();
	InventorySubsystem->OnInventoryUpdated.AddDynamic(this, &ThisClass::UpdateInventory);

	// 创建背包UI
	UClass* BpInventoryClass = LoadObject<UClass>(nullptr, BpInventoryClassPath);
	if (!ensure(BpInventoryClass)) return;

	InventoryUI = Cast<UMixInventoryWidget>(
		UUserWidget::CreateWidgetInstance(*GetGameInstance(), BpInventoryClass, TEXT("Inventory")));
	if (!ensure(InventoryUI)) return;
	InventoryUI->AddToViewport();

	UClass* BpItemClass = LoadObject<UClass>(nullptr, BpItemClassPath);
	if (!ensure(BpItemClass)) return;
}

void UMixUISubsystem::UpdateInventory()
{
	if (!ensure(InventoryUI->Grid)) return;

	// 清理背包UI网格的ItemWidget
	for (const auto& ItemWidget : ItemUIPool)
	{
		InventoryUI->Grid->RemoveChild(ItemWidget.Get());
	}

	// 清理ItemUIPool引用池
	ItemUIPool.Empty();

	// 重新生成背包内全部ItemWidget
	UMixInventorySubsystem* InventorySubsystem = GetGameInstance()->GetSubsystem<UMixInventorySubsystem>();
	for (const auto& [ItemTID, InventoryItem] : InventorySubsystem->InventoryItems)
	{
		if (!ensure(InventoryItem)) continue;
		if (!ensure(InventorySubsystem->AllItemsCfg.Contains(InventoryItem->TID))) continue;
		if (!ensure(InventorySubsystem->AllItemsCfg[InventoryItem->TID]->Icon)) continue;

		// 生成ItemWidget
		UMixItemWidget* ItemWidget = Cast<UMixItemWidget>(UUserWidget::CreateWidgetInstance(*GetGameInstance(), BpItemClass, TEXT("Item")));
		if (!ensure(ItemWidget)) continue;

		ItemWidget->OwnerWidget = InventoryUI;
		ItemWidget->OwnerGrid = InventoryUI->Grid;
		ItemWidget->PosIdx = InventoryItem->PosIdx;
		ItemWidget->ItemTID = InventoryItem->TID;
		ItemWidget->Img->SetBrushFromTexture(InventorySubsystem->AllItemsCfg[InventoryItem->TID]->Icon);
		ItemUIPool.Add(ItemWidget);

		// ItemWidget添加到Grid
		int32 Row = InventoryItem->PosIdx / 3;
		int32 Col = InventoryItem->PosIdx % 3;
		InventoryUI->Grid->AddChildToUniformGrid(ItemWidget, Row, Col);
	}
}

void UMixUISubsystem::CreateTestBtnUI()
{
}

void UMixUISubsystem::Deinitialize()
{
	Super::Deinitialize();
}