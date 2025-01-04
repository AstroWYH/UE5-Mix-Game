// Copyright Epic Games, Inc. All Rights Reserved.

#include "MixCreature.h"

#include "MixAssetManager.h"
#include "MixWidgetComponent.h"
#include "Components/WidgetComponent.h"
#include "Creature/Component/MixAttackComponent.h"
#include "Creature/Component/Attack/MixCreatureAttackComponent.h"
#include "Data/Attribute/MixAttributeData.h"
#include "Data\WidgetComponent\MixWidgetComponentAsset.h"
#include "UI/HeadUI/MixHeadUIWidget.h"

AMixCreature::AMixCreature() : Super()
{
	WidgetComponentFix = CreateDefaultSubobject<UMixWidgetComponent>(TEXT("WidgetComponentFix"));
	WidgetComponentFix->SetupAttachment(RootComponent);

	AttackComponent = CreateDefaultSubobject<UMixAttackComponent>(TEXT("AttackComponent"));
}

void AMixCreature::BeginPlay()
{
	Super::BeginPlay();
}

void AMixCreature::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMixCreature::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();

	const UMixWidgetComponentAsset& HeadUIAsset = UMixAssetManager::Get().GetOrLoadAssetData<UMixWidgetComponentAsset>(
		UMixAssetManager::Get().HeadUIAsset);
	if (!(HeadUIAsset.Classes.Contains(GetClass()->GetFName()))) return;

	TSubclassOf<UUserWidget> HeadUIClass = HeadUIAsset.Classes[GetClass()->GetFName()];
	HeadUI = CreateWidget<UMixHeadUIWidget>(GetWorld(), HeadUIClass);
	if (!ensure(HeadUI)) return;
	if (!ensure(WidgetComponentFix)) return;
	
	WidgetComponentFix->SetWidget(HeadUI);
	HeadUI->SetOwner(this);
}
