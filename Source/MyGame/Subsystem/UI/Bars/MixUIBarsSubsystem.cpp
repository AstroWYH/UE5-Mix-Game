// Fill out your copyright notice in the Description page of Project Settings.


#include "MixUIBarsSubsystem.h"

#include "Character/Host/MixHost.h"
#include "Component/Health/MixCharacterHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MixUIMgrSubsystem.h"
#include "UI/Bars/MixBarsContainerWidget.h"

void UMixUIBarsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UIModulePath = TEXT("UI/Bars/");

	Super::Initialize(Collection);

	// GetGameInstance()->GetGameViewportClient()->OnPlayerAdded().AddUObject(this, &ThisClass::OnTakeDamage);
}

void UMixUIBarsSubsystem::LoadUIClass()
{
	Super::LoadUIClass();

	UMixUIMgrSubsystem* UISubsystem = GetGameInstance()->GetSubsystem<UMixUIMgrSubsystem>();
	BpBarContainerClass = UISubsystem->LoadUIClass(UIModulePath, TEXT("WB_BarsContainer.WB_BarsContainer_C"));
	BpHealthClass = UISubsystem->LoadUIClass(UIModulePath, TEXT("WB_HealthBar.WB_HealthBar_C"));
	BpMagicClass = UISubsystem->LoadUIClass(UIModulePath, TEXT("WB_MagicBar.WB_MagicBar_C"));
}

void UMixUIBarsSubsystem::BindUpdateUIEvent()
{
	Super::BindUpdateUIEvent();
}

void UMixUIBarsSubsystem::OnTakeDamage(int32 LocalUserNum)
{
	AMixHost* Host = Cast<AMixHost>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!ensure(Host)) return;
	if (!ensure(Host->CharacterHeathComponent)) return;

	Host->CharacterHeathComponent->OnCharacterTakeDamage.AddDynamic(this, &ThisClass::UpdateUIBars);
}

void UMixUIBarsSubsystem::CreatePersistantUI()
{
	Super::CreatePersistantUI();

	BarsContainerUI = Cast<UMixBarsContainerWidget>(
		UUserWidget::CreateWidgetInstance(*GetGameInstance(), BpBarContainerClass, TEXT("BarsContainer")));
	if (!ensure(BarsContainerUI)) return;

	BarsContainerUI->AddToViewport();
}

void UMixUIBarsSubsystem::UpdateUIBars(int32 DamageVal)
{
}

void UMixUIBarsSubsystem::Deinitialize()
{
	Super::Deinitialize();
}