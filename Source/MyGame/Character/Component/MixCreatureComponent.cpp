// Fill out your copyright notice in the Description page of Project Settings.


#include "MixCreatureComponent.h"
#include "Character/MixCreature.h"


// Sets default values for this component's properties
UMixCreatureComponent::UMixCreatureComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMixCreatureComponent::BeginPlay()
{
	Super::BeginPlay();

	Creature = Cast<AMixCreature>(GetOwner());
	if (!ensure(Creature.IsValid())) return;
}


// Called every frame
void UMixCreatureComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}