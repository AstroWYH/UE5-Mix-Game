// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "MixAbilityBase.generated.h"

class AMixHero;

UCLASS()
class MYGAME_API AMixAbilityBase : public AActor
{
	GENERATED_BODY()

public:
	AMixAbilityBase();

	UPROPERTY(EditDefaultsOnly)
	TArray<FSoftObjectPath> Montages;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<AMixHero> Hero;

	FGameplayTag Type;
};
