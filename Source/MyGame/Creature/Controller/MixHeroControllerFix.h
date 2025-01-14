// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MixAIController.h"
#include "MixControllerInterface.h"
#include "MixHeroControllerFix.generated.h"

class AMixHero;
class AMixCreature;

UENUM(BlueprintType, Blueprintable)
enum class ETargetType : uint8
{
	AgainstHero,
	FindHero,
	FindBatman,
	Max,
};

UENUM(BlueprintType, Blueprintable)
enum class EObserveCreatureType : uint8
{
	Hero,
	Batman,
	Tower,
	Max,
};

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
	void MoveToAttackTarget(ETargetType Type);

	UFUNCTION(BlueprintCallable)
	void MoveToClosedBatman();

	virtual void OnTargetPerceptionUpdated(AActor* Actor, struct FAIStimulus Stimulus) override;

	virtual void SetAttacker(AMixCreature* InAttacker) override;

private:
	struct FTimerHandle BattleTimerHandle;

	AMixHero* Hero;

	AMixHero* FindHero;
};
