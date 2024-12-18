// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Creature/Component/Health/MixCreatureHealthComponent.h"
#include "MixHeroHealthComponent.generated.h"


UCLASS()
class MYGAME_API UMixHeroHealthComponent : public UMixCreatureHealthComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMixHeroHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,  FActorComponentTickFunction* ThisTickFunction) override;
};
