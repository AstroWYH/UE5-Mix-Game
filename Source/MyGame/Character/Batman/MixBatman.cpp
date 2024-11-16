// Copyright Epic Games, Inc. All Rights Reserved.

#include "MixBatman.h"
#include "Character\Batman\MixBatmanAttackComponent.h"

AMixBatman::AMixBatman()
{
	BatmanAttackComponent = CreateDefaultSubobject<UMixBatmanAttackComponent>(TEXT("BatmanAttackComponent"));
}
