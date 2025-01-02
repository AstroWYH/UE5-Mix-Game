// Copyright Epic Games, Inc. All Rights Reserved.

#include "MixBatman.h"

#include "MixAssetManager.h"
#include "Components/WidgetComponent.h"
#include "Creature/Component/Attack/Batman/MixBatmanAttackComponent.h"
#include "Creature/Component/Health/Batman/MixBatmanHealthComponent.h"
#include "Creature/Creature/MixAttribute.h"
#include "Data/Attribute/MixAttributeData.h"

AMixBatman::AMixBatman() : Super()
{
	CreatureAttackComponent = CreateDefaultSubobject<UMixBatmanAttackComponent>(TEXT("BatmanAttackComponent"));
	CreatureHeathComponent = CreateDefaultSubobject<UMixBatmanHealthComponent>(TEXT("BatmanHealthComponent"));
}

void AMixBatman::BeginPlay()
{
	Super::BeginPlay();
}