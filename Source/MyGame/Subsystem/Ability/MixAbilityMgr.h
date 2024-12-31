// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MixTickGameInstanceSubsystem.h"

#include "MixAbilityMgr.generated.h"

class AMixAbilityBase;
struct FGameplayTag;

UCLASS()
class MYGAME_API UMixAbilityMgr : public UMixTickGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual bool Tick(float DeltaTime) override;

public:
	void PerformAbility(FGameplayTag HeroName, FGameplayTag AbilityKey);

private:
	void TurnToMousePos();

	void TickTurnToMousePos();
	
private:
	TMap<FGameplayTag, TMap<FGameplayTag, AMixAbilityBase>> HeroAbilityData;

};