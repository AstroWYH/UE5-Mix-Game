// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MixGameSubsystem.h"

#include "MixAbilityMgr.generated.h"

class AMixHero;
class AMixAbilityBase;
struct FGameplayTag;

USTRUCT(BlueprintType)
struct FMixAbilityData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TMap<FGameplayTag, AMixAbilityBase*> Data;
};

struct FMixHeroTurnData
{
	FMixHeroTurnData()
	{
		Reset();
	}
	
	void Reset()
	{
		SelfLocation = FVector::ZeroVector;
		SelfRotation = FRotator::ZeroRotator;
		TargetLocation = FVector::ZeroVector;
		SelfLookAtRotation = FRotator::ZeroRotator;
		TotalYawDifference = 0.0f;
		bNeedRotate = false;
		KRotationTime = 0.3f;
		YawPerFrame = 0.0f;
		CurAbilityKey = FGameplayTag();
	}

	// 旋转朝向数据
	FVector SelfLocation;
	FRotator SelfRotation;
	FVector TargetLocation;
	FRotator SelfLookAtRotation;
	float TotalYawDifference = 0.0f;
	bool bNeedRotate = false;
	float KRotationTime = 0.3f;
	float YawPerFrame = 0.0f;
	FGameplayTag CurAbilityKey;
};

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
	void PrepareAbility(AMixHero* Hero, const FGameplayTag& AbilityKey, const FVector& AbilityPos);

private:
	void TurnToMousePos(AMixHero* Hero, const FGameplayTag& AbilityKey, const FVector& AbilityPos);

	void TickTurnToMousePos();

public:
	UFUNCTION(BlueprintCallable)
	void OnMontageNoify(AMixHero* Hero);

private:
	UPROPERTY()
	TMap<AMixHero*, FMixAbilityData> HeroAbilityData;

	TMap<AMixHero*, FMixHeroTurnData> TurnData;

public:
	void SetNeedRotate(AMixHero* Hero, bool bInNeedRotate)
	{
		TurnData[Hero].bNeedRotate = bInNeedRotate;
	}

};