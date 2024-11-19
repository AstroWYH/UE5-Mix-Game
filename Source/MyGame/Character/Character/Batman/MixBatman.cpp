// Copyright Epic Games, Inc. All Rights Reserved.

#include "MixBatman.h"
#include "Character/Component/Attack/Batman/MixBatmanAttackComponent.h"
#include "Component/Health/Batman/MixBatmanHealthComponent.h"

AMixBatman::AMixBatman() : Super()
{
	CharacterAttackComponent2 = CreateDefaultSubobject<UMixBatmanAttackComponent>(TEXT("BatmanAttackComponent2"));
	CharacterHeathComponent =  CreateDefaultSubobject<UMixBatmanHealthComponent>(TEXT("BatmanHealthComponent"));
}

void AMixBatman::BeginPlay()
{
	Super::BeginPlay();

}
