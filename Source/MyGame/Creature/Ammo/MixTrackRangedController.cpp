// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature/Ammo/MixTrackRangedController.h"

#include "MixTrackRangedAmmo.h"
#include "Creature/Ammo/Hero/MixHeroAmmo.h"
#include "Creature/Creature/MixCreature.h"
#include "Utils/MixGameplayTags.h"

void AMixTrackRangedController::BeginPlay()
{
	Super::BeginPlay();

	// 此时无法获取Pawn，因为SpawnActor<AMixTrackRangedController>的过程中，会执行AMixTrackRangedController::BeginPlay()
	// 然后才会去OnPossess(Pawn)
}

void AMixTrackRangedController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Ammo = Cast<AMixTrackRangedAmmo>(GetPawn());
	if (!ensure(Ammo)) return;

	// 暂时没用
	Ammo->SetTrackController(this);

	// 1. Ammo->XXX()如果在CustomPreSpawnInitalization设置，则此处可以获取；否则，在这里没法获取；现在没用这个功能
	// 2. 使用MoveToActor无法和敌方单位产生碰撞，到靠近Target时，就完成Move了，没办法攻击Target
	// MoveToActor(Ammo->Target.Get(), 0.0f);

	// Controller已经控制Ammo，在BP_AMMO打中敌人后关闭；不关闭也没问题，因为2s会GC
	bTrack = true;
}

void AMixTrackRangedController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTrack)
	{
		bool A = Ammo->IsValidLowLevel();
		bool B = IsValid(Ammo);
		FVector TargetLocation = Ammo->GetTarget()->GetActorLocation();
		TargetLocation.Z += Ammo->AmmoOffset;
		MoveToLocation(TargetLocation, 1.0f, true, false, false);

		float Distance = FVector::Distance(TargetLocation, Ammo->GetActorLocation());
		if (Distance < MixGlobalData::AmmoHiddenDistance) // TODO: 配置
		{
			bTrack = false;
			Ammo->CauseDamage();
			Ammo->SetActorHiddenInGame(true);
		}
	}
}
