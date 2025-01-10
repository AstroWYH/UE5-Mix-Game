// Fill out your copyright notice in the Description page of Project Settings.


#include "MixHeroControllerFix.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Creature/Creature/MixCreature.h"
#include "Perception/AIPerceptionTypes.h"


// Sets default values
AMixHeroControllerFix::AMixHeroControllerFix()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMixHeroControllerFix::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMixHeroControllerFix::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMixHeroControllerFix::MoveToAttackTarget()
{
	MoveToActor(Attacker, 20.f);
}

void AMixHeroControllerFix::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	Super::OnTargetPerceptionUpdated(Actor, Stimulus);

	AMixCreature* Creature = Cast<AMixCreature>(Actor);
	if (Creature)
	{
		bool bIsDetectCreature = Stimulus.WasSuccessfullySensed();

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,
			FString::Printf(
				TEXT("bSensed:%d Actor:%s"), bIsDetectCreature,
				*Actor->GetName()));

		// TODO
	}
}

void AMixHeroControllerFix::SetAttacker(AMixCreature* InAttacker)
{
	Super::SetAttacker(InAttacker);

	Blackboard->SetValueAsObject("TargetHero", InAttacker);
	Blackboard->SetValueAsBool("bUnderHeroAttack", true);

	// TODO: 什么时候脱战，把bUnderHeroAttack置为false
}

