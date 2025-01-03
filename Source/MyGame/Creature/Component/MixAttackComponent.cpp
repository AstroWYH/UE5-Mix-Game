// Fill out your copyright notice in the Description page of Project Settings.


#include "MixAttackComponent.h"

UMixAttackComponent::UMixAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UMixAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UMixAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

