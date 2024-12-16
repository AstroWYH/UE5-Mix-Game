// Fill out your copyright notice in the Description page of Project Settings.


#include "MixUIBarsSubsystem.h"

#include "MixGameInstance.h"
#include "Character/Host/MixHost.h"
#include "Component/Health/MixCharacterHealthComponent.h"
#include "Components/NamedSlot.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Bars/MixBarsContainerWidget.h"
#include "UI/Bars/MixHealthBarWidget.h"
#include "UI/Bars/MixMagicBarWidget.h"

void UMixUIBarsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// UMixGameInstance* GameInstance = Cast<UMixGameInstance>(GetGameInstance());
	// GameInstance->OnSpawnPlayActor.AddUObject(this, &ThisClass::OnSpawnPlayActor);
}

// void UMixUIBarsSubsystem::OnSpawnPlayActor()
// {
// 	AMixHost* Host = Cast<AMixHost>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
// 	if (!ensure(Host)) return;
// 	if (!ensure(Host->CharacterHeathComponent)) return;
//
// 	Host->CharacterHeathComponent->OnCharacterTakeDamage.AddDynamic(this, &ThisClass::UpdateUIBars);
// }

void UMixUIBarsSubsystem::Tick(float DeltaTime)
{
	// Character会在GameInstance的AddLocalPlayer添加，可以注册GameInstance或GameViewportClient的委托
	// GameInstance: OnLocalPlayerAddedEvent
	// GameViewportClient: PlayerAddedDelegate
	// 前者保证Subsystem->Initialize()时，生命周期存在
	// 后者则不存在，需要借助static CreatedDelegate，流程更复杂

	// 在Tick里执行，只有初次起作用，后续存在浪费
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Character)
	{
		AMixHost* Host = Cast<AMixHost>(Character);
		if (!ensure(Host)) return;
		if (!ensure(Host->CharacterHeathComponent)) return;
	
		if (!Host->CharacterHeathComponent->OnCharacterTakeDamage.IsBound())
		{
			Host->CharacterHeathComponent->OnCharacterTakeDamage.AddDynamic(this, &ThisClass::UpdateUIBars);
		}
	}
}

void UMixUIBarsSubsystem::CreateUI()
{
	Super::CreateUI();

	BarsContainerUI = Cast<UUserWidget>(UUserWidget::CreateWidgetInstance(*GetGameInstance(), UIMgr->GetUIClass(GetClass()->GetFName(), "BarsContainer"), TEXT("BarsContainer")));
	if (!ensure(BarsContainerUI)) return;

	UNamedSlot* BarsNS = Cast<UNamedSlot>(UIMgr->GetMainLayoutSlots()["Bars"]);
	BarsNS->SetContent(BarsContainerUI);
}

void UMixUIBarsSubsystem::BindUIEvent()
{
	Super::BindUIEvent();
}

void UMixUIBarsSubsystem::UpdateUIBars(int32 DamageVal)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,
	                                 FString::Printf(TEXT("GetDamage: %d"), DamageVal));
}

void UMixUIBarsSubsystem::Deinitialize()
{
	Super::Deinitialize();
}