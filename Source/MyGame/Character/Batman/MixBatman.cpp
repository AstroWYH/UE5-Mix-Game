// Copyright Epic Games, Inc. All Rights Reserved.

#include "MixBatman.h"
#include "Character\Batman\MixBatmanAttackComponent.h"

AMixBatman::AMixBatman() : Super()
{
// 	TestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
// 	TestMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent2"));
// 	TestMesh3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent3"));
// 	BatmanAttackComponent = CreateDefaultSubobject<UMixBatmanAttackComponent>(TEXT("BatmanAttackComponent1"));
	CharacterAttackComponent2 = CreateDefaultSubobject<UMixBatmanAttackComponent>(TEXT("BatmanAttackComponent2"));
//  CharacterAttackComponent = CreateDefaultSubobject<UMixBatmanAttackComponent>(TEXT("BatmanAttackComponent"));
}

void AMixBatman::BeginPlay()
{
	Super::BeginPlay();

}
