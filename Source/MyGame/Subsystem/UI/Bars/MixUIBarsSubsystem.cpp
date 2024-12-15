// Fill out your copyright notice in the Description page of Project Settings.


#include "MixUIBarsSubsystem.h"

#include "MixGameInstance.h"
#include "Character/Host/MixHost.h"
#include "Component/Health/MixCharacterHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Bars/MixBarsContainerWidget.h"
#include "UI/Bars/MixHealthBarWidget.h"
#include "UI/Bars/MixMagicBarWidget.h"

void UMixUIBarsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UMixGameInstance* GameInstance = Cast<UMixGameInstance>(GetGameInstance());
	// GameInstance->OnSpawnPlayActor.AddUObject(this, &ThisClass::OnSpawnPlayActor);
}

void UMixUIBarsSubsystem::OnSpawnPlayActor()
{
	AMixHost* Host = Cast<AMixHost>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!ensure(Host)) return;
	if (!ensure(Host->CharacterHeathComponent)) return;

	Host->CharacterHeathComponent->OnCharacterTakeDamage.AddDynamic(this, &ThisClass::UpdateUIBars);
}

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

void UMixUIBarsSubsystem::LoadUIClass()
{
	Super::LoadUIClass();

	UMixUIMgr* UIMgr = GetGameInstance()->GetSubsystem<UMixUIMgr>();
	const auto& UIAssetMap = UIMgr->GetAllUIAssets();
	if (!ensure(UIAssetMap.IsValid())) return;
	if (!ensure(UIAssetMap->Contains(GetClass()->GetFName()))) return;

	FUIClassArray UIClassArray = (*UIAssetMap)[GetClass()->GetFName()];
	for (TSubclassOf<UUserWidget> UIClass : UIClassArray.UIClasses)
	{
		if (UIClass->IsChildOf(UMixBarsContainerWidget::StaticClass()))
		{
			BpBarContainerClass = UIClass;
		}
		if (UIClass->IsChildOf(UMixHealthBarWidget::StaticClass()))
		{
			BpHealthClass = UIClass;
		}
		if (UIClass->IsChildOf(UMixMagicBarWidget::StaticClass()))
		{
			BpMagicClass = UIClass;
		}
	}
}

void UMixUIBarsSubsystem::CreateUI()
{
	Super::CreateUI();

	BarsContainerUI = Cast<UMixBarsContainerWidget>(
		UUserWidget::CreateWidgetInstance(*GetGameInstance(), BpBarContainerClass, TEXT("BarsContainer")));
	if (!ensure(BarsContainerUI)) return;

	BarsContainerUI->AddToViewport();
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