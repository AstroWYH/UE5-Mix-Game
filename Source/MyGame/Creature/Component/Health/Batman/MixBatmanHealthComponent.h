// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Creature/Component/Health/MixCreatureHealthComponent.h"
#include "MixBatmanHealthComponent.generated.h"


UCLASS()
class MYGAME_API UMixBatmanHealthComponent : public UMixCreatureHealthComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMixBatmanHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
