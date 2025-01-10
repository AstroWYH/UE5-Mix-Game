// Fill out your copyright notice in the Description page of Project Settings.


#include "MixAIController.h"

#include "Perception/AIPerceptionComponent.h"


// Sets default values
AMixAIController::AMixAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMixAIController::BeginPlay()
{
	Super::BeginPlay();

	// TODO: 找一个时机，在Cpp这个父类里，添加AIPerception的组件
}

// Called every frame
void AMixAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMixAIController::Bp_PostBeginPlay()
{
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated);
}

void AMixAIController::OnTargetPerceptionUpdated(AActor* Actor, struct FAIStimulus Stimulus)
{
	
}
