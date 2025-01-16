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

protected:
	AMixCreature* Attacker = nullptr;

public:
	AMixCreature* GetAttacker() const
	{
		return Attacker;
	}

	virtual void UnderHeroAttack(AMixCreature* InAttacker)
	{
		this->Attacker = InAttacker;
	}

protected:
	FTimerHandle UnderAttackTimerHandle;

	AMixCreature* Creature;

	AMixCreature* TargetCreature;

	TMap<uint32, AMixCreature*> CreaturesInSight;
};