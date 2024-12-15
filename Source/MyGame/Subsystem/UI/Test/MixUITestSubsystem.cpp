// Fill out your copyright notice in the Description page of Project Settings.


#include "MixUITestSubsystem.h"
#include "Components/Button.h"
#include "Inventory/MixInventorySubsystem.h"
#include "UI/Test/MixTestBtnWidget.h"

void UMixUITestSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UMixUITestSubsystem::LoadUIClass()
{
	Super::LoadUIClass();

	UMixUIMgr* UIMgr = GetGameInstance()->GetSubsystem<UMixUIMgr>();
	const auto& UIAssetMap = UIMgr->GetAllUIAssets();
	if (!ensure(UIAssetMap.IsValid())) return;
	if (!ensure(UIAssetMap->Contains(GetClass()->GetFName()))) return;

	FUIClassArray UIClassArray = (*UIAssetMap)[GetClass()->GetFName()];
	for (TSubclassOf<UUserWidget> UIClass : UIClassArray.UIClasses)
	{
		if (UIClass->IsChildOf(UMixTestBtnWidget::StaticClass()))
		{
			BpTestUIClass = UIClass;
		}
	}
}

void UMixUITestSubsystem::CreateUI()
{
	Super::CreateUI();
	
	TestBtnUI = Cast<UUserWidget>(
		UUserWidget::CreateWidgetInstance(*GetGameInstance(), BpTestUIClass, TEXT("TestBtn")));
	if (!ensure(TestBtnUI)) return;

	UMixUIMgr* UIMgr = GetGameInstance()->GetSubsystem<UMixUIMgr>();
	UIMgr->GetUIBPData(TestBtnUI, BPVarDataMap);

	TestBtnUI->AddToViewport();
}

void UMixUITestSubsystem::BindUIEvent()
{
	Super::BindUIEvent();

	// 在创建UMG时，通过反射Bind变量，非必要不创建cpp父类
	// TestBtnUI->BtnAdd->OnClicked.AddDynamic(this, &ThisClass::TestAdd);
	// TestBtnUI->BtnRemove->OnClicked.AddDynamic(this, &ThisClass::TestRemove);

	UButton* BtnAdd = Cast<UButton>(BPVarDataMap["BtnAdd"]);
	BtnAdd->OnClicked.AddDynamic(this, &ThisClass::TestAdd);

	UButton* BtnRemove = Cast<UButton>(BPVarDataMap["BtnRemove"]);
	BtnRemove->OnClicked.AddDynamic(this, &ThisClass::TestRemove);
}

void UMixUITestSubsystem::TestAdd()
{
	UMixInventorySubsystem* InventorySubsystem = GetGameInstance()->GetSubsystem<UMixInventorySubsystem>();
	InventorySubsystem->InventoryTestAddBtn();
}

void UMixUITestSubsystem::TestRemove()
{
	UMixInventorySubsystem* InventorySubsystem = GetGameInstance()->GetSubsystem<UMixInventorySubsystem>();
	InventorySubsystem->InventoryTestRemoveBtn();
}

void UMixUITestSubsystem::Deinitialize()
{
	Super::Deinitialize();
}