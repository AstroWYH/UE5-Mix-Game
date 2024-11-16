// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MixAIBatmanController.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API AMixAIBatmanController : public AAIController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	void OnPossess(APawn* InPawn) override;

public:
	UFUNCTION(BlueprintCallable, Category = "AMixAIBatmanController")
	void PostBpBeginPlay();

public:
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, struct FAIStimulus Stimulus);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMixAIBatmanController")
	TSubclassOf<AActor> PathPointClass;

	TArray<FVector> PathPointsPos;

// 	const TCHAR* BehaviorTreePath{ TEXT("/Script/AIModule.BehaviorTree'/Game/MixGame/Character/EnemyBatman/AI/BatmanBt.BatmanBt'") };
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMixAIBatmanController")
// 	TObjectPtr<UBehaviorTree> BehaviorTree;

	class UAIPerceptionComponent* BatmanAIPerceptionComponent = nullptr;

	class UBlackboardComponent* BatmanBlackboard = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMixAIBatmanController")
	bool bIsDetectHost = false;
};
