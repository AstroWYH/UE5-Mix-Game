// Fill out your copyright notice in the Description page of Project Settings.


#include "MixHeroControllerFix.h"

#include "Algo/MinElement.h"
#include "Batman/MixAIBatmanController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Creature/Component/MixAttackComponent.h"
#include "Creature/Creature/MixAttribute.h"
#include "Creature/Creature/MixCreature.h"
#include "Creature/Creature/MixHeroAttribute.h"
#include "Creature/Creature/MixTower.h"
#include "Creature/Creature/Batman/MixBatman.h"
#include "Creature/Creature/Hero/MixHero.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Level/MixLevelSubsystem.h"
#include "Perception/AIPerceptionTypes.h"

AMixHeroControllerFix::AMixHeroControllerFix()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMixHeroControllerFix::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AMixHeroControllerFix::BeginPlay()
{
	Super::BeginPlay();
}

void AMixHeroControllerFix::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMixHeroControllerFix::MoveToClosedBatman()
{
	UMixLevelSubsystem* LevelSubsystem = GetWorld()->GetSubsystem<UMixLevelSubsystem>();
	if (!ensure(LevelSubsystem)) return;

	TArray<AMixBatman*> Batmans = LevelSubsystem->GetSpawnedBatmans();
	FVector SelfLocation = Creature->GetActorLocation();
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
		if (!(FindCreature->GetCreatureCamp() == Creature->GetCreatureCamp()))
		{
			bool bIsDetectCreature = Stimulus.WasSuccessfullySensed();
			GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Yellow, FString::Printf(TEXT("%s %d %s"), *(UUMixTagHelper::GetLastNameFromGameplayTag(Creature->GetCreatureName()) + FString::FromInt(Creature->GetId())), bIsDetectCreature, *(UUMixTagHelper::GetLastNameFromGameplayTag(FindCreature->GetCreatureName()) + FString::FromInt(FindCreature->GetId()))));

			// 动态维护CreaturesInSight
			if (bIsDetectCreature)
			{
				CreaturesInSight.Add(FindCreature->GetId(), FindCreature);
			}
			else
			{
				CreaturesInSight.Remove(FindCreature->GetId());
			}

			// 优先目标为EnemyHero
			if (EnemyHero)
			{
				TargetCreature = EnemyHero;
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

void AMixHeroControllerFix::UnderEnemyHeroAttack(AMixCreature* InAttacker)
{
	Super::UnderEnemyHeroAttack(InAttacker);

	Blackboard->SetValueAsBool(MixGlobalData::BB_bUnderAttack, true);
	TargetCreature = EnemyHero;
	Blackboard->SetValueAsObject(MixGlobalData::BB_TargetCreature, TargetCreature);

	// 通知附近友方Batman, Tower
	NotifyNearbyFriendCamp();

	// 如果未受到Hero攻击，则3s后脱战
	if (UnderAttackTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(UnderAttackTimerHandle);
	}

	GetWorld()->GetTimerManager().SetTimer(UnderAttackTimerHandle, [this]()
	{
		Blackboard->SetValueAsBool(MixGlobalData::BB_bUnderAttack, false);
		EnemyHero = nullptr;
		TargetCreature = GetClosestTarget();
		Blackboard->SetValueAsObject(MixGlobalData::BB_TargetCreature, TargetCreature);

		UnderAttackTimerHandle.Invalidate();
	}, MixGlobalData::UnderAttackTime, false);
}

void AMixHeroControllerFix::NotifyNearbyFriendCamp() const
{
	// 通知友方阵营Batman & Tower，Hero受到攻击
	TArray<FHitResult> OutHits;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1), UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel5)};
	UKismetSystemLibrary::CapsuleTraceMultiForObjects(GetWorld(), Creature->GetActorLocation(), Creature->GetActorLocation(), MixGlobalData::FriendCampPerceptionRadius, MixGlobalData::CapsuleDetectionHalfHeight, ObjectTypes, false, TArray<AActor*>(), EDrawDebugTrace::None, OutHits, true);
	for (const FHitResult& Hit : OutHits)
	{
		AActor* HitActor = Hit.GetActor();
		if (!ensure(HitActor)) continue;
		AMixCreature* HitCreature = Cast<AMixCreature>(HitActor);
		// 仅通知友方阵营
		if (HitCreature->GetCreatureCamp() != Creature->GetCreatureCamp()) continue;
		
		AMixAIController* AIController = Cast<AMixAIController>(HitCreature->GetController());
		AIController->FriendHeroUnderAttack(EnemyHero, Creature);
	}
}