// Fill out your copyright notice in the Description page of Project Settings.


#include "MixRangedAmmo.h"

#include "Creature/Component/Health/MixCreatureHealthComponent.h"
#include "Creature/Creature/MixAttribute.h"
#include "Creature/Creature/MixCreature.h"


// Sets default values
AMixRangedAmmo::AMixRangedAmmo()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMixRangedAmmo::BeginPlay()
{
	Super::BeginPlay();

	DestroySelf();
}

// Called every frame
void AMixRangedAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMixRangedAmmo::CauseDamage()
{
	int32 AttackVal = Target->GetAttribute()->AttackVal;
	Target->GetAttribute()->ApplyHealth(Attacker, -AttackVal);
}

void AMixRangedAmmo::DestroySelf()
{
	// 2s后自毁，允许蓝图重新实现，这只是尝试教学
	// 也可以把秒数拿来用UProperty配置
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, [this]()
	{
		Destroy();
	}, 2.0f, false);
}

