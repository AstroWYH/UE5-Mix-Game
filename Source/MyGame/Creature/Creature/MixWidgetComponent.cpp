// Fill out your copyright notice in the Description page of Project Settings.


#include "MixWidgetComponent.h"

#include "MixAttribute.h"
#include "MixCreature.h"


// Sets default values for this component's properties
UMixWidgetComponent::UMixWidgetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMixWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	AMixCreature* Creature = Cast<AMixCreature>(GetOwner());
	if (!ensure(Creature)) return;

	Creature->GetAttribute()->OnApplyHealth.AddDynamic(this, &ThisClass::OnHealthChange);
}


// Called every frame
void UMixWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMixWidgetComponent::OnHealthChange(int32 ApplyVal, int32 Health, int32 MaxHealth)
{
	UUserWidget* HeadUI = GetWidget();

}

