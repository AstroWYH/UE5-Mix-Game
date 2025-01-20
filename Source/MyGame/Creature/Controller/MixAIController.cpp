// Fill out your copyright notice in the Description page of Project Settings.


#include "MixAIController.h"

#include "Algo/MinElement.h"
#include "Creature/Component/MixAttackComponent.h"
#include "Creature/Creature/MixAttribute.h"
#include "Creature/Creature/MixCreature.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "Utils/MixGameplayTags.h"


AMixAIController::AMixAIController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMixAIController::BeginPlay()
{
	Super::BeginPlay();

}

void AMixAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMixAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Creature = Cast<AMixCreature>(GetPawn());
}

void AMixAIController::BP_PostBeginPlay()
{
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated);
}

void AMixAIController::OnTargetPerceptionUpdated(AActor* Actor, struct FAIStimulus Stimulus)
{
	
}

AMixCreature* AMixAIController::GetClosestTarget() const
{
	FVector SelfLocation = Creature->GetActorLocation();
	TArray<AMixCreature*> CreaturesArray;
	CreaturesInSight.GenerateValueArray(CreaturesArray);
	AMixCreature** ClosestCreature = Algo::MinElementBy(CreaturesArray, [SelfLocation, this](const AMixCreature* InCreature)
	{
		return FVector::Distance(SelfLocation, InCreature->GetActorLocation());
	});
	if (!(ClosestCreature)) return nullptr;

	return *ClosestCreature;
}

void AMixAIController::MoveToTarget()
{
	SetFocus(TargetCreature);
	MoveToActor(TargetCreature, MixGlobalData::MoveDiff);
}

bool AMixAIController::IsTargetInRange()
{
	float Distance = FVector::Distance(Creature->GetActorLocation(), TargetCreature->GetActorLocation());
	if (Distance < Creature->GetAttribute()->AttackRange)
	{
		return true;
	}
	
	return false;
}

void AMixAIController::AttackTarget()
{
	// FLatentActionInfo LatentInfo;
	// LatentInfo.CallbackTarget = this;
	// LatentInfo.ExecutionFunction = FName("OnDelayFinished");
	// UKismetSystemLibrary::Delay(GetWorld(), 1.0f, LatentInfo);

	UMixAttackComponent::FindAttackComponent(Creature)->PrepareAttack(TargetCreature);
}

void AMixAIController::OnDelayFinished()
{
	UMixAttackComponent::FindAttackComponent(Creature)->PrepareAttack(TargetCreature);
}

void AMixAIController::FriendHeroUnderAttack(AMixCreature* InEnemyHero, AMixCreature* InFriendHero)
{
}
