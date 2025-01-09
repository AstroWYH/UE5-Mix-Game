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

	HeadUI = CreateWidget<UMixHeadUIWidget>(GetWorld(), UMixAssetManager::Get().HeadUIWidget);
	if (!ensure(HeadUI)) return;
	if (!ensure(WidgetComponentFix)) return;
	
	WidgetComponentFix->SetWidget(HeadUI);
	HeadUI->SetOwner(this);
}
