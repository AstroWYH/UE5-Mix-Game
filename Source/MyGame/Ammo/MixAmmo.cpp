// Fill out your copyright notice in the Description page of Project Settings.

#include "Ammo/MixAmmo.h"
#include "TimerManager.h"
#include "Character/MixCharacter.h"
#include "Component/Health/MixCharacterHealthComponent.h"

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
	AMixCharacter* TargetCharacter = Cast<AMixCharacter>(Target);
	if (!ensure(TargetCharacter)) return;

	TargetCharacter->CharacterHeathComponent->TakeDamage(DamageVal);
}