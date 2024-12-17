// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo/MixAIAmmoController.h"
#include "Ammo\Host\MixHeroAmmo.h"

void AMixAIAmmoController::BeginPlay()
{
	Super::BeginPlay();

	// 此时无法获取Pawn，因为SpawnActor<AMixAIAmmoController>的过程中，会执行AMixAIAmmoController::BeginPlay()
	// 而此时还没OnPossess(Pawn)
}

void AMixAIAmmoController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

	Ammo = Cast<AMixAmmo>(GetPawn());
	if (!ensure(Ammo.IsValid())) return;
	if (!ensure(Ammo->Target.IsValid())) return;

	// Ammo->Target如果不在CustomPreSpawnInitalization设置，则此处获取不到
	// 使用MoveToActor无法和敌方单位产生碰撞
	// MoveToActor(Ammo->Target.Get(), 0.0f);
	bCanLaunch = true;

}

void AMixAIAmmoController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanLaunch)
	{
		FVector TargetLocation = Ammo->Target->GetActorLocation();
		TargetLocation.Z += Ammo->AmmoOffset;
		MoveToLocation(TargetLocation, 1.0f, true, false, false);
	}
}
