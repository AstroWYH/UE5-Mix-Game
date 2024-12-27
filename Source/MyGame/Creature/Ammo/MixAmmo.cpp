// Fill out your copyright notice in the Description page of Project Settings.

#include "Creature/Ammo/MixAmmo.h"
#include "TimerManager.h"
#include "Creature/Creature/MixCreature.h"
#include "Creature/Component/Health/MixCreatureHealthComponent.h"

// Sets default values
AMixAmmo::AMixAmmo()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMixAmmo::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMixAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMixAmmo::HitTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                         int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AMixAmmo::MakeDamage(int32 DamageVal)
{
	AMixCreature* TargetCreature = Cast<AMixCreature>(Target);
	if (!ensure(TargetCreature)) return;

	TargetCreature->CreatureHeathComponent->TakeDamage(DamageVal);
}