// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Creature/Controller/MixAIController.h"
#include "MixAIBatmanController.generated.h"

class AMixBatman;
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

	virtual void Bp_PostBeginPlay() override;

	virtual void OnTargetPerceptionUpdated(AActor* Actor, struct FAIStimulus Stimulus) override;
	

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<FVector> PathPointsPos;

	AMixBatman* Batman;
};
