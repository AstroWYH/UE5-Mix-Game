// Fill out your copyright notice in the Description page of Project Settings.


#include "MixHeroHealthComponent.h"


// Sets default values for this component's properties
UMixHeroHealthComponent::UMixHeroHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// TODO: 后续改为配表
	CurHealth = 800;
	MaxHealth = 800;
}


// Called when the game starts
void UMixHeroHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMixHeroHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

