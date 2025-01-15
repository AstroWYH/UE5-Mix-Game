// Fill out your copyright notice in the Description page of Project Settings.


#include "MixHeroControllerFix.h"

#include "Algo/MinElement.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Creature/Creature/MixAttribute.h"
#include "Creature/Creature/MixCreature.h"
#include "Creature/Creature/MixHeroAttribute.h"
#include "Creature/Creature/Batman/MixBatman.h"
#include "Creature/Creature/Hero/MixHero.h"
#include "Level/MixLevelSubsystem.h"
#include "Perception/AIPerceptionTypes.h"

AMixHeroControllerFix::AMixHeroControllerFix()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMixHeroControllerFix::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Hero = Cast<AMixHero>(GetPawn());
}

void AMixHeroControllerFix::BeginPlay()
{
	Super::BeginPlay();
}

void AMixHeroControllerFix::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMixHeroControllerFix::MoveToAttackTarget()
{
	// TODO: 暂时用move代替，暂定一个距离
	SetFocus(TargetCreature);
	MoveToActor(TargetCreature, MixGlobalData::MoveDiff);
}

void AMixHeroControllerFix::MoveToClosedBatman()
{
	UMixLevelSubsystem* LevelSubsystem = GetWorld()->GetSubsystem<UMixLevelSubsystem>();
	if (!ensure(LevelSubsystem)) return;

	TArray<AMixBatman*> Batmans = LevelSubsystem->GetSpawnedBatmans();
	FVector SelfLocation = Hero->GetActorLocation();
	AMixBatman** ClosestBatman = Algo::MinElementBy(Batmans, [SelfLocation, this](const AMixBatman* Batman)
	{
		return FVector::Distance(SelfLocation, Batman->GetActorLocation());
	});
	if (!(ClosestBatman)) return;

	// TODO: 暂时用move代替，暂定一个距离
	MoveToActor(*ClosestBatman, MixGlobalData::MoveDiff);
}

void AMixHeroControllerFix::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	Super::OnTargetPerceptionUpdated(Actor, Stimulus);

	if (AMixCreature* FindCreature = Cast<AMixCreature>(Actor))
	{
		// 仅处理不同阵营
		if (!(FindCreature->GetCreatureCamp()== Hero->GetCreatureCamp()))
		{
			bool bIsDetectCreature = Stimulus.WasSuccessfullySensed();
			GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Yellow, FString::Printf(TEXT("%d %s"), bIsDetectCreature, *Actor->GetName()));
			
			// 动态维护TargetCreatures
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

AMixCreature* AMixHeroControllerFix::GetClosestTarget()
{
	FVector SelfLocation = Hero->GetActorLocation();
	TArray<AMixCreature*> CreaturesArray;
	CreaturesInSight.GenerateValueArray(CreaturesArray);
	AMixCreature** ClosestCreature = Algo::MinElementBy(CreaturesArray, [SelfLocation, this](const AMixCreature* InCreature)
	{
		return FVector::Distance(SelfLocation, InCreature->GetActorLocation());
	});
	if (!(ClosestCreature)) return nullptr;
	
	return *ClosestCreature;
}

void AMixHeroControllerFix::SetAttacker(AMixCreature* InAttacker)
{
	Super::SetAttacker(InAttacker);

	uint32 AttackerId = InAttacker->GetId();
	Blackboard->SetValueAsBool(MixGlobalData::BB_bUnderAttack, true);
	TargetCreature = InAttacker;
	Blackboard->SetValueAsObject(MixGlobalData::BB_TargetCreature, TargetCreature);

	// 如果未受到攻击，则3s后脱战
	if (BattleTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(BattleTimerHandle);
	}

	GetWorld()->GetTimerManager().SetTimer(BattleTimerHandle, [this]()
	{
		Blackboard->SetValueAsBool(MixGlobalData::BB_bUnderAttack, false);
		Attacker = nullptr;
		TargetCreature = GetClosestTarget();
		Blackboard->SetValueAsObject(MixGlobalData::BB_TargetCreature, TargetCreature);

		BattleTimerHandle.Invalidate();
	}, MixGlobalData::BattleTime, false);
}
