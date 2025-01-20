// Fill out your copyright notice in the Description page of Project Settings.


#include "MixAIBatmanController.h"

#include "MixAssetManager.h"
#include "Algo/MinElement.h"
#include "Utils/MixGameplayTags.h"
#include "Kismet\GameplayStatics.h"
#include "BehaviorTree\BehaviorTree.h"
#include "BehaviorTree\BlackboardComponent.h"
#include "Creature/Component/MixAttackComponent.h"
#include "Creature/Controller/MixHeroControllerFix.h"
#include "Creature/Creature/MixAttribute.h"
#include "Creature/Creature/Batman/MixBatman.h"
#include "Perception\AIPerceptionTypes.h"
#include "Perception\AIPerceptionComponent.h"
#include "Creature/Creature/Hero/MixHero.h"
#include "Kismet\GameplayStatics.h"
#include "Utils/UMixTagHelper.h"

// 此时无法获取Pawn
void AMixAIBatmanController::BeginPlay()
{
	Super::BeginPlay();
}

void AMixAIBatmanController::BeginDestroy()
{
	Super::BeginDestroy();
}

void AMixAIBatmanController::BP_PostBeginPlay()
{
	Super::BP_PostBeginPlay();

	// Init Batman蓝/红路径点
	TArray<AActor*> PathPoints;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), UMixAssetManager::Get().BatmanModelInfo[MixGameplayTags::Creature_Name_Batman].PathPoint, MixGlobalData::PathPoint_Batman, PathPoints);

	PathPoints.Sort([](const AActor& A, const AActor& B) -> bool
	{
		const int32 ANum = UUMixTagHelper::ConvertNumberFromFName(A.Tags[0]);
		const int32 BNum = UUMixTagHelper::ConvertNumberFromFName(B.Tags[0]);
		return ANum < BNum;
	});

	for (const auto& PathPoint : PathPoints)
	{
		if (!ensure(PathPoint)) continue;
		PathPointsPos_Blue.Add(PathPoint->GetActorLocation());
	}
	PathPointsPos_Red = PathPointsPos_Blue;
	Algo::Reverse(PathPointsPos_Red);

	Blackboard->SetValueAsInt(MixGlobalData::BB_CurTargetIdx, 0);
}

void AMixAIBatmanController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	Super::OnTargetPerceptionUpdated(Actor, Stimulus);

	if (AMixCreature* FindCreature = Cast<AMixCreature>(Actor))
	{
		// 处理敌方阵营
		if (!(FindCreature->GetCreatureCamp() == Creature->GetCreatureCamp()))
		{
			bool bIsDetectCreature = Stimulus.WasSuccessfullySensed();
			GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Cyan, FString::Printf(TEXT("%s %d %s"), *(UUMixTagHelper::GetLastNameFromGameplayTag(Creature->GetCreatureName()) + FString::FromInt(Creature->GetId())), bIsDetectCreature, *(UUMixTagHelper::GetLastNameFromGameplayTag(FindCreature->GetCreatureName()) + FString::FromInt(FindCreature->GetId()))));

			// 动态维护CreaturesInSight
			if (bIsDetectCreature)
			{
				CreaturesInSight.Add(FindCreature->GetId(), FindCreature);
			}
			else
			{
				CreaturesInSight.Remove(FindCreature->GetId());
			}

			// 优先目标为EnmeyHero
			if (EnmeyHero)
			{
				TargetCreature = EnmeyHero;
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

void AMixAIBatmanController::FriendHeroUnderAttack(AMixCreature* EnemyHero, AMixCreature* FriendHero)
{
	Blackboard->SetValueAsBool(MixGlobalData::BB_bFriendHeroUnderAttack, true);
	TargetCreature = EnemyHero;
	EnmeyHero = EnemyHero;
	Blackboard->SetValueAsObject(MixGlobalData::BB_TargetCreature, TargetCreature);

	// 如果友方Hero未受到Hero攻击，则3s后脱战
	if (UnderAttackTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(UnderAttackTimerHandle);
	}

	GetWorld()->GetTimerManager().SetTimer(UnderAttackTimerHandle, [this]()
	{
		Blackboard->SetValueAsBool(MixGlobalData::BB_bFriendHeroUnderAttack, false);
		EnmeyHero = nullptr;
		TargetCreature = GetClosestTarget();
		Blackboard->SetValueAsObject(MixGlobalData::BB_TargetCreature, TargetCreature);

		UnderAttackTimerHandle.Invalidate();
	}, MixGlobalData::UnderAttackTime, false);
}

void AMixAIBatmanController::Patrol()
{
	if (Creature->GetCreatureCamp() == MixGameplayTags::Creature_Camp_Blue)
	{
		MoveToLocation(PathPointsPos_Blue[CurTargetIdx], MixGlobalData::PatrolDiff);
	}
	else if (Creature->GetCreatureCamp() == MixGameplayTags::Creature_Camp_Red)
	{
		MoveToLocation(PathPointsPos_Red[CurTargetIdx], MixGlobalData::PatrolDiff);
	}
}

void AMixAIBatmanController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Creature->GetCreatureCamp() == MixGameplayTags::Creature_Camp_Blue)
	{
		float Distance = FVector::Distance(Creature->GetActorLocation(), PathPointsPos_Blue[CurTargetIdx]);
		if (Distance <= MixGlobalData::CheckPatrolDiff)
		{
			if (CurTargetIdx < PathPointsPos_Blue.Num() - 1)
			{
				CurTargetIdx++;
				Blackboard->SetValueAsInt(MixGlobalData::BB_CurTargetIdx, CurTargetIdx);
			}
		}
	}
	else if (Creature->GetCreatureCamp() == MixGameplayTags::Creature_Camp_Red)
	{
		float Distance = FVector::Distance(Creature->GetActorLocation(), PathPointsPos_Red[CurTargetIdx]);
		if (Distance <= MixGlobalData::CheckPatrolDiff)
		{
			if (CurTargetIdx < PathPointsPos_Red.Num() - 1)
			{
				CurTargetIdx++;
				Blackboard->SetValueAsInt(MixGlobalData::BB_CurTargetIdx, CurTargetIdx);
			}
		}
	}
}

void AMixAIBatmanController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}