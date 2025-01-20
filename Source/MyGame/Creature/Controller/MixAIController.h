// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MixAIController.generated.h"

class AMixCreature;

UCLASS(Abstract)
class MYGAME_API AMixAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMixAIController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void BP_PostBeginPlay();

	UFUNCTION() // AddDynamic
	virtual void OnTargetPerceptionUpdated(AActor* Actor, struct FAIStimulus Stimulus);
	
	AMixCreature* GetClosestTarget() const;

	UFUNCTION(BlueprintCallable)
	void MoveToTarget();

	UFUNCTION(BlueprintCallable)
	bool IsTargetInRange();

	UFUNCTION(BlueprintCallable)
	void AttackTarget();
	
	void OnDelayFinished();

	virtual void FriendHeroUnderAttack(AMixCreature* InEnemyHero, AMixCreature* InFriendHero);

protected:
	AMixCreature* EnemyHero = nullptr;

public:
	AMixCreature* GetEnemyHero() const
	{
		return EnemyHero;
	}

	virtual void UnderEnemyHeroAttack(AMixCreature* InAttacker)
	{
		this->EnemyHero = InAttacker;
	}

protected:
	FTimerHandle UnderAttackTimerHandle;

	AMixCreature* Creature;

	AMixCreature* TargetCreature;

	TMap<uint32, AMixCreature*> CreaturesInSight;
};