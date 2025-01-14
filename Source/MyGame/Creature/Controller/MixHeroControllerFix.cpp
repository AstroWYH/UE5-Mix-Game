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

	if (FindHero)
	{
		bool bIsHealthGreater = static_cast<float>(Hero->GetAttribute()->Health) / Hero->GetAttribute()->MaxHealth >= static_cast<float>(FindHero->GetAttribute()->Health) / FindHero->GetAttribute()->MaxHealth;
		Blackboard->SetValueAsBool(MixGlobalData::BB_bHealthGreater, bIsHealthGreater);
	}
}

void AMixHeroControllerFix::MoveToAttackTarget(ETargetType Type)
{
	// TODO: 暂时用move代替，暂定一个距离
	AMixCreature* TargetCreature = nullptr;
	if (Type == ETargetType::AgainstHero)
	{
		TargetCreature = Attacker;
	}
	else if (Type == ETargetType::FindHero || Type == ETargetType::FindBatman)
	{
		TargetCreature = Cast<AMixCreature>(Blackboard->GetValueAsObject(MixGlobalData::BB_TargetCreature));
	}

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
	if (!ensure(ClosestBatman)) return;

	// TODO: 暂时用move代替，暂定一个距离
	MoveToActor(*ClosestBatman, MixGlobalData::MoveDiff);
}

void AMixHeroControllerFix::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	Super::OnTargetPerceptionUpdated(Actor, Stimulus);

	if (AMixCreature* FindCreature = Cast<AMixCreature>(Actor))
	{
		bool bIsDetectCreature = Stimulus.WasSuccessfullySensed();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("bSensed:%d Actor:%s"), bIsDetectCreature, *Actor->GetName()));

		Blackboard->SetValueAsObject(MixGlobalData::BB_TargetCreature, FindCreature);

		FindHero = Cast<AMixHero>(FindCreature);
		if (FindHero)
		{
			if (!(FindHero->GetCreatureCamp()== Hero->GetCreatureCamp()))
			{
				Blackboard->SetValueAsBool(MixGlobalData::BB_bFindEnemyHero, bIsDetectCreature);

				bool bIsHealthGreater = static_cast<float>(Hero->GetAttribute()->Health) / Hero->GetAttribute()->MaxHealth >= static_cast<float>(FindHero->GetAttribute()->Health) / FindHero->GetAttribute()->MaxHealth;
				Blackboard->SetValueAsBool(MixGlobalData::BB_bHealthGreater, bIsHealthGreater);
			}
		}
		else if (AMixBatman* FindBatman = Cast<AMixBatman>(FindCreature))
		{
			if (!(FindBatman->GetCreatureCamp()== Hero->GetCreatureCamp()))
			{
				Blackboard->SetValueAsBool(MixGlobalData::BB_bFindEnemyBatman, bIsDetectCreature);
			}
		}
	}
}

void AMixHeroControllerFix::SetAttacker(AMixCreature* InAttacker)
{
	Super::SetAttacker(InAttacker);

	Blackboard->SetValueAsObject(MixGlobalData::BB_TargetCreature, InAttacker);
	Blackboard->SetValueAsBool(MixGlobalData::BB_bUnderAttack, true);

	Cast<UMixHeroAttribute>(Hero->GetAttribute())->CheckHealth(this);

	if (BattleTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(BattleTimerHandle);
	}

	GetWorld()->GetTimerManager().SetTimer(BattleTimerHandle, [this]()
	{
		Blackboard->SetValueAsObject(MixGlobalData::BB_TargetCreature, nullptr);
		Blackboard->SetValueAsBool(MixGlobalData::BB_bUnderAttack, false);

		BattleTimerHandle.Invalidate();
	}, MixGlobalData::BattleTime, false);
}