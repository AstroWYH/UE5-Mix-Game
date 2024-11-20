// Fill out your copyright notice in the Description page of Project Settings.


#include "MixUIBarsSubsystem.h"

#include "Character/Host/MixHost.h"
#include "Component/Health/MixCharacterHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MixUISubsystem.h"
#include "UI/Bars/MixBarsContainerWidget.h"

void UMixUIBarsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// TODO: 整理到datatable
	UMixUISubsystem* UISubsystem = GetGameInstance()->GetSubsystem<UMixUISubsystem>();
	BpBarContainerClass = UISubsystem->LoadUIResource(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MixGame/UI/Bars/WB_BarsContainer.WB_BarsContainer_C'"));
	BpHealthClass = UISubsystem->LoadUIResource(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MixGame/UI/Bars/WB_HealthBar.WB_HealthBar_C'"));
	BpMagicClass = UISubsystem->LoadUIResource(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MixGame/UI/Bars/WB_MagicBar.WB_MagicBar_C'"));

	RegisterSelf();

	AMixHost* Host = Cast<AMixHost>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!ensure(Host)) return;
	if (!ensure(Host->CharacterHeathComponent)) return;

	Host->CharacterHeathComponent->OnCharacterTakeDamage.AddDynamic(this, &ThisClass::UpdateUIBars);
}

void UMixUIBarsSubsystem::CreateUI()
{
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
	UnRegisterSelf();

	Super::Deinitialize();
}