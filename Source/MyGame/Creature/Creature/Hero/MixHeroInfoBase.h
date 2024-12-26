// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MixHero.h"
#include "GameFramework/Actor.h"

#include "MixHeroInfoBase.generated.h"

struct FStreamableHandle;
class AMixHero;

enum class EHeroOperateKey
{
	NoType = 0,
	NormalAttack = 1,
	Q = 2,
	W = 3,
	E = 4,
	R = 5,
	MAX,
};

UCLASS()
class AMixHeroInfoBase : public AActor
{
	GENERATED_BODY()

public:
	AMixHeroInfoBase();

	void Init();

	void StopMovement();

	void TurnToMousePos();

	void TickTurnToMousePos();

	void PlaySkillMontage();

	virtual void Tick(float DeltaSeconds) override;

public:
	virtual void Skill(EHeroOperateKey SkillKey) {}

public:
	UFUNCTION(BlueprintCallable)
	virtual void SkillSpawn() {}

public:
	void SetHero(AMixHero* InHero);

	TWeakObjectPtr<AMixHero> GetHero() const;

	// 配置是否智能施法
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIntelligentCasting_Q = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIntelligentCasting_W = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIntelligentCasting_E = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIntelligentCasting_R = false;

protected:
	TWeakObjectPtr<AMixHero> Hero;
	FSoftObjectPath* SkillMontagePath = nullptr;
	EHeroOperateKey CurSkillKey;
	TMap<EHeroOperateKey, TSharedPtr<FStreamableHandle>> SkillMontageHandles;

	// 朝向目标参数
	FVector SelfLocation;
	FRotator SelfRotation;
	FVector TargetLocation;
	FRotator SelfLookAtRotation;
	float TotalYawDifference = 0.0f;
	bool bIsRotating = false;
	float KRotationTime = 0.3f;
	float YawPerFrame = 0.0f;

protected:
	FVector SkillCastMousePos;

public:
	void SetIsRotating(bool bIsRotating);

	void SetSkillCastMousePos(FVector SkillCastMousePos);

};