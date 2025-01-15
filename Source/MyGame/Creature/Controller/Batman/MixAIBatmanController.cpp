// Fill out your copyright notice in the Description page of Project Settings.


#include "MixAIBatmanController.h"

#include "MixAssetManager.h"
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

			// 动态维护TargetCreatures
			if (bIsDetectCreature)
			{
				CreaturesInSight.Add(FindCreature->GetId(), FindCreature);
			}
			else
			{
				CreaturesInSight.Remove(FindCreature->GetId());
			}
			// Blackboard->SetValueAsObject(MixGlobalData::BB_TargetCreature, FindCreature);
		}
	}
}

// TODO: Decorator里，如果执行该装饰器，则该函数每帧调用
bool AMixAIBatmanController::CheckNearbyHeros()
{
	// TArray<FHitResult> OutHits;
	// TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel3)};
	// UKismetSystemLibrary::CapsuleTraceMultiForObjects(GetWorld(), Batman->GetActorLocation(), Batman->GetActorLocation(), MixGlobalData::BatmanPerceptionRadius, MixGlobalData::CapsuleDetectionHalfHeight, ObjectTypes, false, TArray<AActor*>(), EDrawDebugTrace::None, OutHits, true);
	//
	// for (const FHitResult& Hit : OutHits)
	// {
	// 	AActor* HitActor = Hit.GetActor();
	// 	if (!ensure(HitActor)) continue;
	// 	AMixHero* HitHero = Cast<AMixHero>(HitActor);
	// 	if (!ensure(HitHero)) continue;
	// 	// 处理敌方阵营
	// 	if (HitHero->GetCreatureCamp() != Batman->GetCreatureCamp()) continue;
	//
	// 	UBlackboardComponent* HeroBB = Cast<AMixHeroControllerFix>(HitHero->GetController())->GetBlackboardComponent();
	// 	bool bHeroUnderAttack = HeroBB->GetValueAsBool(MixGlobalData::BB_bUnderAttack);
	// 	if (bHeroUnderAttack)
	// 	{
	// 		TargetCreature = HitHero;
	// 		Blackboard->SetValueAsObject(MixGlobalData::BB_TargetCreature, TargetCreature);
	//
	// 		// 如果未受到攻击，则3s后脱战
	// 		if (BattleTimerHandle.IsValid())
	// 		{
	// 			GetWorld()->GetTimerManager().ClearTimer(BattleTimerHandle);
	// 		}
	//
	// 		GetWorld()->GetTimerManager().SetTimer(BattleTimerHandle, [this]()
	// 		{
	// 			Blackboard->SetValueAsBool(MixGlobalData::BB_bUnderAttack, false);
	// 			Attacker = nullptr;
	// 			TargetCreature = GetClosestTarget();
	// 			Blackboard->SetValueAsObject(MixGlobalData::BB_TargetCreature, TargetCreature);
	//
	// 			BattleTimerHandle.Invalidate();
	// 		}, MixGlobalData::BattleTime, false);
	// 		return true;
	// 	}
	// }
	//
	return false;
}

void AMixAIBatmanController::MoveToAttackTarget()
{
	// TODO: 暂时用move代替，暂定一个距离
	SetFocus(TargetCreature);
	MoveToActor(TargetCreature, MixGlobalData::MoveDiff);
}

void AMixAIBatmanController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AMixAIBatmanController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}