// Copyright Epic Games, Inc. All Rights Reserved.

#include "MixCreature.h"

#include "Components/WidgetComponent.h"
#include "Creature/Component/Attack/MixCreatureAttackComponent.h"

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

	HeadUI = CreateWidget<UUserWidget>(GetGameInstance(), HeadUIClass);
	HeadComponent->SetWidget(HeadUI);
}
