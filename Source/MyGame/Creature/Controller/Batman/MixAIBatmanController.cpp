// Fill out your copyright notice in the Description page of Project Settings.


#include "MixAIBatmanController.h"

#include "MixAssetManager.h"
#include "MixGameplayTags.h"
#include "Kismet\GameplayStatics.h"
#include "BehaviorTree\BehaviorTree.h"
#include "BehaviorTree\BlackboardComponent.h"
#include "Creature/Creature/Batman/MixBatman.h"
#include "Perception\AIPerceptionTypes.h"
#include "Perception\AIPerceptionComponent.h"
#include "Creature/Creature/Hero/MixHero.h"
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

	Batman = Cast<AMixBatman>(GetPawn());
}

void AMixAIBatmanController::BeginDestroy()
{
	Super::BeginDestroy();
}

void AMixAIBatmanController::Bp_PostBeginPlay()
{
	Super::Bp_PostBeginPlay();

	// 存Batman路径点
	TArray<AActor*> PathPonits;
	// TODO: 后续近战小兵，可能要改这个Tag
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), UMixAssetManager::Get().CreatureModelInfo[MixGameplayTags::Creature_Name_Batman].PathPoint, "BatmanPathPoint", PathPonits);
	for (const auto& PathPoint : PathPonits)
	{
		if (!ensure(PathPoint)) continue;
		PathPointsPos.Add(PathPoint->GetActorLocation());
	}

	// Init黑板
	Blackboard->SetValueAsInt("NextPatrolIdx", 0);

	// // Find蓝图BatmanAIPerception TODO: 直接获取，AIController提供了获取的接口，但需要自己Set
	// TArray<UActorComponent*> TaggedComponents = GetComponentsByTag(UActorComponent::StaticClass(), "BatmanAIPerception");
	// for (UActorComponent* Component : TaggedComponents)
	// {
	// 	if (!ensure(Component)) continue;
	// 	BatmanAIPerceptionComponent = Cast<UAIPerceptionComponent>(Component);
	// 	if (!ensure(BatmanAIPerceptionComponent)) continue;
	//
	// 	BatmanAIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMixAIBatmanController::OnTargetPerceptionUpdated);
	// }
}

// void AMixAIBatmanController::TraceTarget()
// {
// 	AMixHero* Hero = Cast<AMixHero>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
// 	// 接近300停止 
// 	MoveToActor(Hero, 300.0f);
// }
// 
// void AMixAIBatmanController::TraceTargetAbort()
// {
// 	if (!bIsDetectCreature)
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
// 	if (bIsDetectCreature)
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
	Super::OnTargetPerceptionUpdated(Actor, Stimulus);
	
	// Ammo也能检测到，在此拦截
	AMixCreature* Creature = Cast<AMixCreature>(Actor);
	if (Creature)
	{
		bool bIsDetectCreature = Stimulus.WasSuccessfullySensed();

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,
			FString::Printf(
				TEXT("bSensed:%d Actor:%s"), bIsDetectCreature,
				*Actor->GetName()));

		Blackboard->SetValueAsBool("IsDetectCreature", bIsDetectCreature);
		Blackboard->SetValueAsObject("Creature", Creature);
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
