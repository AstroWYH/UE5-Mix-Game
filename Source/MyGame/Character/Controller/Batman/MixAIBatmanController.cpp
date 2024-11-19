// Fill out your copyright notice in the Description page of Project Settings.


#include "MixAIBatmanController.h"
#include "Kismet\GameplayStatics.h"
#include "BehaviorTree\BehaviorTree.h"
#include "BehaviorTree\BlackboardComponent.h"
#include "Perception\AIPerceptionTypes.h"
#include "Perception\AIPerceptionComponent.h"
#include "Character/Character/Host/MixHost.h"
#include "Kismet\GameplayStatics.h"

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

void AMixAIBatmanController::BeginDestroy()
{
	Super::BeginDestroy();

	if (!ensure(BatmanAIPerceptionComponent)) return;
	BatmanAIPerceptionComponent->OnTargetPerceptionUpdated.RemoveAll(this);
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

// void AMixAIBatmanController::TraceTarget()
// {
// 	AMixHost* Host = Cast<AMixHost>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
// 	// 接近300停止 
// 	MoveToActor(Host, 300.0f);
// }
// 
// void AMixAIBatmanController::TraceTargetAbort()
// {
// 	if (!bIsDetectHost)
// 	{
// 		StopMovement();
// 
// 		OnMovementAbort.Broadcast();
// 	}
// }
// 
// void AMixAIBatmanController::TracePathPoint()
// {
// 	int32 NextPatrolIdx = BatmanBlackboard->GetValueAsInt("NextPatrolIdx");
// 	if (!ensure(PathPointsPos.IsValidIndex(NextPatrolIdx))) return;
// 
// 	FVector NextPathPointPos = PathPointsPos[NextPatrolIdx];
// 	MoveToLocation(NextPathPointPos, -1);
// }
// 
// void AMixAIBatmanController::TracePathPointComplete()
// {
// 	int32 NextPatrolIdx = BatmanBlackboard->GetValueAsInt("NextPatrolIdx");
// 	BatmanBlackboard->SetValueAsInt("NextPatrolIdx", ++NextPatrolIdx);
// }
// 
// void AMixAIBatmanController::TracePathPointAbort()
// {
// 	if (bIsDetectHost)
// 	{
// 		StopMovement();
// 
// 		int32 NextPatrolIdx = BatmanBlackboard->GetValueAsInt("NextPatrolIdx");
// 		BatmanBlackboard->SetValueAsInt("NextPatrolIdx", --NextPatrolIdx);
// 
// 		OnMovementAbort.Broadcast();
// 	}
// }
// 
// void AMixAIBatmanController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
// {
// 	Super::OnMoveCompleted(RequestID, Result);
// 
// 	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("AIMoveResult: %d"), Result.Code));
// }

void AMixAIBatmanController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	AMixHost* Host = Cast<AMixHost>(Actor);
	if (Host)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("bSensed: %d Actor:%s"), Stimulus.WasSuccessfullySensed(), *Actor->GetName()));

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
