// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MixAIController.h"
#include "MixControllerInterface.h"
#include "Creature/Creature/MixCreature.h"
#include "MixHeroControllerFix.generated.h"

class AMixHero;
class AMixCreature;
struct FTimerHandle;

// UENUM(BlueprintType, Blueprintable)
// enum class ETargetType : uint8
// {
// 	AgainstHero,
// 	FindHero,
// 	FindBatman,
// 	Max,
// };

UCLASS()
class MYGAME_API AMixHeroControllerFix : public AMixAIController, public IMixControllerInterface
{
	GENERATED_BODY()

public:
	AMixHeroControllerFix();

	virtual void OnPossess(APawn* InPawn) override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void MoveToAttackTarget();

	UFUNCTION(BlueprintCallable)
	void MoveToClosedBatman();

	virtual void OnTargetPerceptionUpdated(AActor* Actor, struct FAIStimulus Stimulus) override;

	virtual void UnderHeroAttack(AMixCreature* InAttacker) override;

private:
	AMixHero* Hero;

	TMap<uint32, AMixCreature*> CreaturesInSight;

	AMixCreature* TargetCreature;

	AMixCreature* GetClosestTarget() const;

	void NotifyNearbyFriendBatman() const;

// public:
// 	DECLARE_MULTICAST_DELEGATE_TwoParams(FMixOnUnderHeroAttack, AMixCreature* Attacker, AMixCreature* Victim);
// 	FMixOnUnderHeroAttack OnAIControllerPostBeginPlay;
};
