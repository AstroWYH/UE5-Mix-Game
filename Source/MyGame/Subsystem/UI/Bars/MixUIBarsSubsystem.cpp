// Fill out your copyright notice in the Description page of Project Settings.


#include "MixUIBarsSubsystem.h"

#include "Creature/Creature/Hero/MixHero.h"
#include "Creature/Component/Health/MixCreatureHealthComponent.h"
#include "Components/NamedSlot.h"
#include "Components/ProgressBar.h"
#include "Creature/Creature/MixAttribute.h"
#include "Kismet/GameplayStatics.h"
#include "Level/MixLevelSubsystem.h"
#include "UI/Bars/MixBarsContainerWidget.h"

void UMixUIBarsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// UMixGameInstance* GameInstance = Cast<UMixGameInstance>(GetGameInstance());
	// GameInstance->OnSpawnPlayActor.AddUObject(this, &ThisClass::OnSpawnPlayActor);
}

// void UMixUIBarsSubsystem::OnSpawnPlayActor()
// {
// 	AMixHero* Hero = Cast<AMixHero>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
// 	if (!ensure(Hero)) return;
// 	if (!ensure(Hero->CreatureHeathComponent)) return;
//
// 	Hero->CreatureHeathComponent->OnCharacterTakeDamage.AddDynamic(this, &ThisClass::UpdateUIBars);
// }

void UMixUIBarsSubsystem::Tick(float DeltaTime)
{
	// Character会在GameInstance的AddLocalPlayer添加，可以注册GameInstance或GameViewportClient的委托
	// GameInstance: OnLocalPlayerAddedEvent
	// GameViewportClient: PlayerAddedDelegate
	// 前者保证Subsystem->Initialize()时，生命周期存在
	// 后者则不存在，需要借助static CreatedDelegate，流程更复杂

	// 在Tick里执行，只有初次起作用，后续存在浪费
	// ACharacter* Creature = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	// if (Creature)
	// {
	// 	AMixHero* Hero = Cast<AMixHero>(Creature);
	// 	if (!ensure(Hero)) return;
	// 	if (!ensure(Hero->CreatureHeathComponent)) return;
	//
	// 	if (!Hero->CreatureHeathComponent->OnCharacterTakeDamage.IsBound())
	// 	{
	// 		Hero->CreatureHeathComponent->OnCharacterTakeDamage.AddDynamic(this, &ThisClass::UpdateUIBars);
	// 	}
	// }
}

void UMixUIBarsSubsystem::CreateUI()
{
	Super::CreateUI();

	BarsContainerUI = Cast<UUserWidget>(UUserWidget::CreateWidgetInstance(*GetGameInstance(), UIMgr->GetUIClass(GetClass()->GetFName(), "BarsContainer"), TEXT("BarsContainer")));
	if (!ensure(BarsContainerUI)) return;

	UNamedSlot* BarsNS = Cast<UNamedSlot>(UIMgr->GetMainLayoutSlots()["Bars"]);
	BarsNS->SetContent(BarsContainerUI);

	UIMgr->GetUIBPData(BarsContainerUI, BPUIProps);
	UUserWidget* HealthBar = Cast<UUserWidget>(BPUIProps["HealthBar"]);
	UIMgr->GetUIBPData(HealthBar, BPUIProps);
	HealthProgress = Cast<UProgressBar>(BPUIProps["Progress"]);
}

void UMixUIBarsSubsystem::BindUIEvent()
{
	Super::BindUIEvent();
}

void UMixUIBarsSubsystem::UpdateUIBars(int32 DamageVal, int32 CurHealthVal, int32 MaxHealthVal)
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("GetDamage: %d"), DamageVal));

	HealthProgress->SetPercent((float)CurHealthVal / MaxHealthVal);
}

void UMixUIBarsSubsystem::Deinitialize()
{
	Super::Deinitialize();

	UMixLevelSubsystem* LevelSubsystem = GetWorld()->GetSubsystem<UMixLevelSubsystem>();
	if (!(LevelSubsystem)) return;

	AMixHero* HostHero = LevelSubsystem->GetHostHero();
	if (HostHero)
	{
		HostHero->GetAttribute()->OnApplyHealth.RemoveAll(this);
	}
}

void UMixUIBarsSubsystem::OnHeroSpawned()
{
	Super::OnHeroSpawned();

	UMixLevelSubsystem* LevelSubsystem = GetWorld()->GetSubsystem<UMixLevelSubsystem>();
	if (!(LevelSubsystem)) return;

	AMixHero* HostHero = LevelSubsystem->GetHostHero();
	if (HostHero)
	{
		HostHero->GetAttribute()->OnApplyHealth.AddDynamic(this, &ThisClass::UpdateUIBars);
	}
}
