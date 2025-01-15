// Fill out your copyright notice in the Description page of Project Settings.


#include "MixAIBatmanController.h"

#include "MixAssetManager.h"
#include "Algo/MinElement.h"
#include "Tag/MixGameplayTags.h"
#include "Kismet\GameplayStatics.h"
#include "BehaviorTree\BehaviorTree.h"
#include "BehaviorTree\BlackboardComponent.h"
#include "Creature/Controller/MixHeroControllerFix.h"
#include "Creature/Creature/Batman/MixBatman.h"
#include "Perception\AIPerceptionTypes.h"
#include "Perception\AIPerceptionComponent.h"
#include "Creature/Creature/Hero/MixHero.h"
#include "Kismet\GameplayStatics.h"

// 此时无法获取Pawn
void AMixAIBatmanController::BeginPlay()
{
	Super::BeginPlay();

	Batman = Cast<AMixBatman>(GetPawn());

	// TArray<AActor*> OutActors;
	// UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMixHeroControllerFix::StaticClass(), OutActors);
	// for (AActor* Actor : OutActors)
	// {
	// 	AMixHeroControllerFix* HeroController = Cast<AMixHeroControllerFix>(Actor);
	// }
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
}

void AMixAIBatmanController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	Super::OnTargetPerceptionUpdated(Actor, Stimulus);

	if (AMixCreature* FindCreature = Cast<AMixCreature>(Actor))
	{
		// 处理敌方阵营
		if (!(FindCreature->GetCreatureCamp() == Batman->GetCreatureCamp()))
		{
			bool bIsDetectCreature = Stimulus.WasSuccessfullySensed();
			GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Cyan, FString::Printf(TEXT("%d %s"), bIsDetectCreature, *Actor->GetName()));

			// 动态维护CreaturesInSight
			if (bIsDetectCreature)
			{
				CreaturesInSight.Add(FindCreature->GetId(), FindCreature);
			}
			else
			{
				CreaturesInSight.Remove(FindCreature->GetId());
			}
			
			// 优先目标为Attacker
			if (Attacker)
			{
				TargetCreature = Attacker;
			}
			// TargetCreature为空，则选择视野里最近的人
			else if (!TargetCreature)
			{
				TargetCreature = GetClosestTarget();
			}
			// TargetCreature不为空，视野里没有TargetCreature，则更新追踪单位
			else if (TargetCreature && !CreaturesInSight.Contains(TargetCreature->GetId()))
			{
				TargetCreature = GetClosestTarget();
			}
			else
			{
				// TargetCreature不为空，视野里有TargetCreature，则保持追踪
			}
			Blackboard->SetValueAsObject(MixGlobalData::BB_TargetCreature, TargetCreature);
		}
	}
}

void AMixAIBatmanController::MoveToAttackTarget()
{
	// TODO: 暂时用move代替，暂定一个距离; 考虑调用到AttackComponent
	SetFocus(TargetCreature);
	MoveToActor(TargetCreature, MixGlobalData::MoveDiff);
}

AMixCreature* AMixAIBatmanController::GetClosestTarget() const
{
	FVector SelfLocation = Batman->GetActorLocation();
	TArray<AMixCreature*> CreaturesArray;
	CreaturesInSight.GenerateValueArray(CreaturesArray);
	AMixCreature** ClosestCreature = Algo::MinElementBy(CreaturesArray, [SelfLocation, this](const AMixCreature* InCreature)
	{
		return FVector::Distance(SelfLocation, InCreature->GetActorLocation());
	});
	if (!(ClosestCreature)) return nullptr;
	
	return *ClosestCreature;
}

void AMixAIBatmanController::FriendHeroUnderAttack(AMixCreature* EnemyHero, AMixCreature* FriendHero)
{
	Blackboard->SetValueAsBool(MixGlobalData::BB_bFriendHeroUnderAttack, true);
	TargetCreature = EnemyHero;
	Blackboard->SetValueAsObject(MixGlobalData::BB_TargetCreature, TargetCreature);

	// 如果友方Hero未受到Hero攻击，则3s后脱战
	if (UnderAttackTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(UnderAttackTimerHandle);
	}

	GetWorld()->GetTimerManager().SetTimer(UnderAttackTimerHandle, [this]()
	{
		Blackboard->SetValueAsBool(MixGlobalData::BB_bFriendHeroUnderAttack, false);
		TargetCreature = GetClosestTarget();
		Blackboard->SetValueAsObject(MixGlobalData::BB_TargetCreature, TargetCreature);

		UnderAttackTimerHandle.Invalidate();
	}, MixGlobalData::UnderAttackTime, false);
}

void AMixAIBatmanController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AMixAIBatmanController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}