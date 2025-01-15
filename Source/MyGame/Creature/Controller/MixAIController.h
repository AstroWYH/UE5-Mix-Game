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
	// Sets default values for this actor's properties
	AMixAIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void Bp_PostBeginPlay();

	UFUNCTION() // AddDynamic
	virtual void OnTargetPerceptionUpdated(AActor* Actor, struct FAIStimulus Stimulus);

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
	
};
