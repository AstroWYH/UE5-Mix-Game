// Fill out your copyright notice in the Description page of Project Settings.


#include "MixAIController.h"

#include "Perception/AIPerceptionComponent.h"


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

void AMixAIController::Bp_PostBeginPlay()
{
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated);
	// OnAIControllerPostBeginPlay.Broadcast();
}

void AMixAIController::OnTargetPerceptionUpdated(AActor* Actor, struct FAIStimulus Stimulus)
{
	
}
