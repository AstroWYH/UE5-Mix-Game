// Copyright Epic Games, Inc. All Rights Reserved.

#include "MixCreature.h"

#include "MixAssetManager.h"
#include "Components/WidgetComponent.h"
#include "Creature/Component/Attack/MixCreatureAttackComponent.h"
#include "DataTable\WidgetComponent\MixWidgetComponentAsset.h"

AMixCreature::AMixCreature() : Super()
{
	HeadComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HeadComponent"));
}

void AMixCreature::BeginPlay()
{
	Super::BeginPlay();
}

void AMixCreature::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();

	const UMixWidgetComponentAsset& HeadUIAsset = UMixAssetManager::Get().GetHeadUIPath();
	if (!ensure(HeadUIAsset.Classes.Contains(GetClass()->GetFName()))) return;

	TSubclassOf<UUserWidget> HeadUIClass = HeadUIAsset.Classes[GetClass()->GetFName()];
	HeadUI = CreateWidget<UUserWidget>(GetGameInstance(), HeadUIClass);
	HeadComponent->SetWidget(HeadUI);
}
