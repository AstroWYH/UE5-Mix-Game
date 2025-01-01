// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "MixAbilityAsset.generated.h"

USTRUCT(BlueprintType)
struct FAbility
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TMap<FGameplayTag, TSubclassOf<AActor>> Ability;
};

UCLASS()
class MYGAME_API UMixAbilityAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TMap<FGameplayTag, FAbility> HeroAbilitys;
};
