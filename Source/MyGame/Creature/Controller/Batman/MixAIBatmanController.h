// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Creature/Controller/MixAIController.h"
#include "Creature/Creature/MixCreature.h"
#include "MixAIBatmanController.generated.h"

class AMixBatman;
class AMixCreature;
class AMixHero;
/**
 * 
 */
UCLASS()
class MYGAME_API AMixAIBatmanController : public AMixAIController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;

	virtual void BeginDestroy() override;

	void Tick(float DeltaTime) override;

	void OnPossess(APawn* InPawn) override;

	virtual void BP_PostBeginPlay() override;

	virtual void OnTargetPerceptionUpdated(AActor* Actor, struct FAIStimulus Stimulus) override;

public:
	UFUNCTION(BlueprintCallable)
	void Patrol();

private:
	int32 CurTargetIdx = 0;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<FVector> PathPointsPos_Blue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<FVector> PathPointsPos_Red;

	AMixCreature* EnmeyHero;

public:
	void FriendHeroUnderAttack(AMixCreature* EnemyHero, AMixCreature* FriendHero);

};
