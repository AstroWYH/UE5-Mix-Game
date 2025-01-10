// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MixAIController.h"
#include "MixControllerInterface.h"
#include "MixHeroControllerFix.generated.h"

class AMixCreature;

UCLASS()
class MYGAME_API AMixHeroControllerFix : public AMixAIController, public IMixControllerInterface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMixHeroControllerFix();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:
	UFUNCTION(BlueprintCallable)
	void MoveToAttackTarget();

	virtual void OnTargetPerceptionUpdated(AActor* Actor, struct FAIStimulus Stimulus) override;

	virtual void SetAttacker(AMixCreature* InAttacker) override;
};
