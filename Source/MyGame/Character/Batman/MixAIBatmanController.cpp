// Fill out your copyright notice in the Description page of Project Settings.


#include "MixAIBatmanController.h"
#include "Kismet\GameplayStatics.h"
#include "BehaviorTree\BehaviorTree.h"
#include "BehaviorTree\BlackboardComponent.h"
#include "Perception\AIPerceptionTypes.h"
#include "Perception\AIPerceptionComponent.h"
#include "Character\Host\MixHost.h"

// 此时无法获取Pawn
void AMixAIBatmanController::BeginPlay()
{
	Super::BeginPlay();

// 	// 开启行为树
// 	BehaviorTree = FindObject<UBehaviorTree>(nullptr, BehaviorTreePath);
// 	if (!BehaviorTree)
// 	{
// 		BehaviorTree = LoadObject<UBehaviorTree>(nullptr, BehaviorTreePath);
// 	}
// 	RunBehaviorTree(BehaviorTree);
}

void AMixAIBatmanController::PostBpBeginPlay()
{
	// 存Batman路径点
	TArray<AActor*> PathPonits;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), PathPointClass, "PathPoint", PathPonits);
	for (const auto& PathPoint : PathPonits)
	{
		if (!ensure(PathPoint)) continue;
		PathPointsPos.Add(PathPoint->GetActorLocation());
	}

	// Init黑板
	BatmanBlackboard = GetBlackboardComponent();
	if (!ensure(BatmanBlackboard)) return;
	BatmanBlackboard->SetValueAsInt("NextPatrolIdx", 0);

	// Find蓝图BatmanAIPerception
	TArray<UActorComponent*> TaggedComponents = GetComponentsByTag(UActorComponent::StaticClass(), "BatmanAIPerception");
	for (UActorComponent* Component : TaggedComponents)
	{
		if (!ensure(Component)) continue;
		BatmanAIPerceptionComponent = Cast<UAIPerceptionComponent>(Component);
		if (!ensure(BatmanAIPerceptionComponent)) continue;

		BatmanAIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMixAIBatmanController::OnTargetPerceptionUpdated);
	}
}

void AMixAIBatmanController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("bSensed: %d Actor:%s"), Stimulus.WasSuccessfullySensed(), *Actor->GetName()));

	AMixHost* Host = Cast<AMixHost>(Actor);
	if (Host)
	{
		bIsDetectHost = Stimulus.WasSuccessfullySensed();
		BatmanBlackboard->SetValueAsBool("IsDetectHost", bIsDetectHost);
	}
}

void AMixAIBatmanController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

}

void AMixAIBatmanController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
