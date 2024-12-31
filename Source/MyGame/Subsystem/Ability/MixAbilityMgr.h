// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MixGameSubsystem.h"

#include "MixAbilityMgr.generated.h"

class AMixAbilityBase;
struct FGameplayTag;

UCLASS()
class MYGAME_API UMixAbilityMgr : public UMixGameSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;
	
	virtual bool Tick(float DeltaTime);

	virtual void OnHeroSpawned() override;
	
private:
	FTSTicker::FDelegateHandle TickHandle;

public:
	void StopMovement();
	
	void PerformAbility(FGameplayTag HeroName, FGameplayTag AbilityKey);

private:
	void TurnToMousePos();

	void TickTurnToMousePos();
	
private:
	UPROPERTY()
	TMap<FGameplayTag, TMap<FGameplayTag, AMixAbilityBase*>> HeroAbilityData;

};