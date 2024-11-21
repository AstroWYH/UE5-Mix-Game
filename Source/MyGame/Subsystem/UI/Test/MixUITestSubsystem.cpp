// Fill out your copyright notice in the Description page of Project Settings.


#include "MixUITestSubsystem.h"
#include "Components/Button.h"
#include "Inventory/MixInventorySubsystem.h"
#include "UI/MixUIMgrSubsystem.h"
#include "UI/Test/MixTestBtnWidget.h"

void UMixUITestSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UIModulePath = "UI/TestBtn/";

	Super::Initialize(Collection);
}

void UMixUITestSubsystem::LoadUIClass()
{
	Super::LoadUIClass();

	UMixUIMgrSubsystem* UISubsystem = GetGameInstance()->GetSubsystem<UMixUIMgrSubsystem>();
	BpTestUIClass = UISubsystem->LoadUIClass(UIModulePath, TEXT("TestBtn.TestBtn_C"));
}

void UMixUITestSubsystem::BindUpdateUIEvent()
{
	Super::BindUpdateUIEvent();
}

void UMixUITestSubsystem::CreatePersistantUI()
{
	Super::CreatePersistantUI();
	
	TestBtnUI = Cast<UMixTestBtnWidget>(
		UUserWidget::CreateWidgetInstance(*GetGameInstance(), BpTestUIClass, TEXT("TestBtn")));
	if (!ensure(TestBtnUI)) return;

	TestBtnUI->AddToViewport();
	
	BindUIEvent();
}

void UMixUITestSubsystem::BindUIEvent()
{
	Super::BindUIEvent();

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

void UMixUITestSubsystem::Deinitialize()
{
	Super::Deinitialize();
}