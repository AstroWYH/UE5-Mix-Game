// Copyright Epic Games, Inc. All Rights Reserved.

#include "MixBatman.h"
#include "Character/Component/Attack/Batman/MixBatmanAttackComponent.h"
#include "Component/Health/Batman/MixBatmanHealthComponent.h"

AMixBatman::AMixBatman() : Super()
{
	CreatureAttackComponent = CreateDefaultSubobject<UMixBatmanAttackComponent>(TEXT("BatmanAttackComponent2"));
	CreatureHeathComponentSup = CreateDefaultSubobject<UMixBatmanHealthComponent>(TEXT("BatmanHealthComponent"));
}

void AMixBatman::BeginPlay()
{
	Super::BeginPlay();
}