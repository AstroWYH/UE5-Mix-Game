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

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<FSoftObjectPath> Montages;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<AMixHero> Hero;

public:
	TWeakObjectPtr<AMixHero> GetHero() const
	{
		return Hero;
	}

	void SetHero(const TWeakObjectPtr<AMixHero>& InHero)
	{
		this->Hero = InHero;
	}

protected:
	FGameplayTag Type;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void BP_PerformAbility();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnMontageNotify(const FVector& MouseLocation);
};