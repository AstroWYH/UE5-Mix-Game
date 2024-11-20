// Fill out your copyright notice in the Description page of Project Settings.


#include "MixUITestSubsystem.h"
#include "Components/Button.h"
#include "Inventory/MixInventorySubsystem.h"
#include "UI/MixUISubsystem.h"
#include "UI/Test/MixTestBtnWidget.h"

void UMixUITestSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UMixUISubsystem* UISubsystem = GetGameInstance()->GetSubsystem<UMixUISubsystem>();
	BpTestUIClass = UISubsystem->LoadUIResource(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MixGame/UI/TestBtn/TestBtn.TestBtn_C'"));

	RegisterSelf();
}

void UMixUITestSubsystem::Deinitialize()
{
	UnRegisterSelf();
	
	Super::Deinitialize();
}

void UMixUITestSubsystem::CreateUI()
{
	TestBtnUI = Cast<UMixTestBtnWidget>(
		UUserWidget::CreateWidgetInstance(*GetGameInstance(), BpTestUIClass, TEXT("TestBtn")));
	if (!ensure(TestBtnUI)) return;
	TestBtnUI->AddToViewport();

	TestBtnUI->BtnAdd->OnClicked.AddDynamic(this, &ThisClass::TestAdd);
	TestBtnUI->BtnRemove->OnClicked.AddDynamic(this, &ThisClass::TestRemove);
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