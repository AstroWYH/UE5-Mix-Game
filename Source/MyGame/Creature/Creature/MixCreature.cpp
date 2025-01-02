// Copyright Epic Games, Inc. All Rights Reserved.

#include "MixCreature.h"

#include "MixAssetManager.h"
#include "Components/WidgetComponent.h"
#include "Creature/Component/Attack/MixCreatureAttackComponent.h"
#include "Data/Attribute/MixAttributeData.h"
#include "Data\WidgetComponent\MixWidgetComponentAsset.h"

AMixCreature::AMixCreature() : Super()
{
	HeadComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HeadComponent"));
	HeadComponent->SetupAttachment(RootComponent);
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

	const UMixWidgetComponentAsset& HeadUIAsset = UMixAssetManager::Get().GetAsset_HeadUI();
	if (!(HeadUIAsset.Classes.Contains(GetClass()->GetFName()))) return;

	TSubclassOf<UUserWidget> HeadUIClass = HeadUIAsset.Classes[GetClass()->GetFName()];
	HeadUI = CreateWidget<UUserWidget>(GetWorld(), HeadUIClass);
	if (!ensure(HeadUI)) return;

	HeadComponent->SetWidget(HeadUI);
}
