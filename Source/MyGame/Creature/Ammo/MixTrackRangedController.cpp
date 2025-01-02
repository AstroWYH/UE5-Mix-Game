// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature/Ammo/MixTrackRangedController.h"

#include "MixTrackRangedAmmo.h"
#include "Creature/Ammo/Hero/MixHeroAmmo.h"

void AMixTrackRangedController::BeginPlay()
{
	Super::BeginPlay();

	// 此时无法获取Pawn，因为SpawnActor<AMixTrackRangedController>的过程中，会执行AMixTrackRangedController::BeginPlay()
	// 然后才会去OnPossess(Pawn)
}

void AMixTrackRangedController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TrackRangedAmmo = Cast<AMixTrackRangedAmmo>(GetPawn());
	if (!ensure(TrackRangedAmmo.IsValid())) return;
	if (!ensure(TrackRangedAmmo->GetTarget())) return;

	TrackRangedAmmo->SetTrackController(this);

	// 1. TrackRangedAmmo->Target如果不在CustomPreSpawnInitalization设置，则此处获取不到
	// 2. 使用MoveToActor无法和敌方单位产生碰撞，到靠近Target时，就完成Move了，没办法攻击Target
	// MoveToActor(TrackRangedAmmo->Target.Get(), 0.0f);

	// Controller已经控制Ammo，在BP_AMMO里关闭
	bCanLaunch = true;
}

void AMixTrackRangedController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanLaunch)
	{
		FVector TargetLocation = TrackRangedAmmo->GetTarget()->GetActorLocation();
		TargetLocation.Z += TrackRangedAmmo->AmmoOffset;
		MoveToLocation(TargetLocation, 1.0f, true, false, false);
	}
}
