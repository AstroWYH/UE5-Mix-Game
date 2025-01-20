// Fill out your copyright notice in the Description page of Project Settings.


#include "MixTowerController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Creature/Creature/MixCreature.h"
#include "Utils/MixGameplayTags.h"

AMixTowerController::AMixTowerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMixTowerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMixTowerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMixTowerController::FriendHeroUnderAttack(AMixCreature* InEnemyHero, AMixCreature* InFriendHero)
{
	Blackboard->SetValueAsBool(MixGlobalData::BB_bFriendHeroUnderAttack, true);
	TargetCreature = InEnemyHero;
	EnemyHero = InEnemyHero;
	Blackboard->SetValueAsObject(MixGlobalData::BB_TargetCreature, TargetCreature);

	// Blackboard->SetValueAsBool(MixGlobalData::BB_bFriendHeroUnderAttack, false);
	// EnemyHero = nullptr;
	// TargetCreature = GetClosestTarget();
	// Blackboard->SetValueAsObject(MixGlobalData::BB_TargetCreature, TargetCreature);
	//
	// UnderAttackTimerHandle.Invalidate();
}

void AMixTowerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TArray<UActorComponent*> TaggedComponents = Creature->GetComponentsByTag(UActorComponent::StaticClass(), MixGlobalData::AttackRangeComponent);

	UStaticMeshComponent* AttackRangeMeshComponent = Cast<UStaticMeshComponent>(TaggedComponents[0]);
	AttackRangeMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnCreatureStepIn);
	AttackRangeMeshComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnCreatureStepOut);
}

void AMixTowerController::OnCreatureStepIn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMixCreature* FindCreature = Cast<AMixCreature>(OtherActor))
	{
		if (!(FindCreature->GetCreatureCamp() == Creature->GetCreatureCamp()))
		{
			CreaturesInSight.Add(FindCreature->GetId(), FindCreature);

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

void AMixTowerController::OnCreatureStepOut(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AMixCreature* FindCreature = Cast<AMixCreature>(OtherActor))
	{
		if (!(FindCreature->GetCreatureCamp() == Creature->GetCreatureCamp()))
		{
			CreaturesInSight.Remove(FindCreature->GetId());
		}
	}
}
