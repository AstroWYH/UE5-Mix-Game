// Fill out your copyright notice in the Description page of Project Settings.


#include "MixAIBatmanController.h"

#include "MixAssetManager.h"
#include "Tag/MixGameplayTags.h"
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
	
	// 如Ammo也能检测，在此拦截
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
