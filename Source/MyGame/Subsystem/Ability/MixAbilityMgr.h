// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MixGameSubsystem.h"

#include "MixAbilityMgr.generated.h"

class AMixAbilityBase;
struct FGameplayTag;

USTRUCT(BlueprintType)
struct FMixAbilityData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TMap<FGameplayTag, AMixAbilityBase*> Data;
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
	void StopMovement();

	void PerformAbility(AMixHero* InHero, FGameplayTag AbilityKey, FVector InAbilityMouseLocation);

private:
	void TurnToMousePos();

	void TickTurnToMousePos();

public:
	UFUNCTION(BlueprintCallable)
	void OnMontageNoify();

private:
	UPROPERTY()
	TMap<FGameplayTag, FMixAbilityData> HeroAbilityData;

	AMixHero* Hero;

	FGameplayTag CurAbilityKey;

private:
	// 朝向目标参数
	FVector SelfLocation;
	FRotator SelfRotation;
	FVector TargetLocation;
	FRotator SelfLookAtRotation;
	float TotalYawDifference = 0.0f;
	bool bIsRotating = false;
	float KRotationTime = 0.3f; // TODO: 参数配置
	float YawPerFrame = 0.0f;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector AbilityMouseLocation;

public:
	void SetIsRotating(bool InbIsRotating)
	{
		bIsRotating = InbIsRotating;
	}

};