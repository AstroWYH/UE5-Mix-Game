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

public:
	// UFUNCTION(BlueprintCallable, Category = "AMixAIBatmanController")
	// void TraceTarget();
	//
	// UFUNCTION(BlueprintCallable, Category = "AMixAIBatmanController")
	// void TraceTargetAbort();
	//
	// UFUNCTION(BlueprintCallable, Category = "AMixAIBatmanController")
	// void TracePathPoint();
	//
	// UFUNCTION(BlueprintCallable, Category = "AMixAIBatmanController")
	// void TracePathPointComplete();
	//
	// UFUNCTION(BlueprintCallable, Category = "AMixAIBatmanController")
	// void TracePathPointAbort();

public:
	// AIPerceptionComponent
	// UFUNCTION()
	// void OnTargetPerceptionUpdated(AActor* Actor, struct FAIStimulus Stimulus);

	// 不需要重复添加UFUNCTION()
	virtual void OnTargetPerceptionUpdated(AActor* Actor, struct FAIStimulus Stimulus) override;
	
public:
	// // AI Controller
	// void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	//
	// DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMixOnMovementAbort);
	// UPROPERTY(BlueprintAssignable)
	// FMixOnMovementAbort OnMovementAbort;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FVector> PathPointsPos;

	// const TCHAR* BehaviorTreePath{ TEXT("/Script/AIModule.BehaviorTree'/Game/MixGame/Character/EnemyBatman/AI/BatmanBt.BatmanBt'") };
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMixAIBatmanController")
	// TObjectPtr<UBehaviorTree> BehaviorTree;

	// class UAIPerceptionComponent* BatmanAIPerceptionComponent = nullptr;

private:
	AMixBatman* Batman;
};
