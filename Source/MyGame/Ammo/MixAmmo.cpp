// Fill out your copyright notice in the Description page of Project Settings.

#include "Ammo/MixAmmo.h"
#include "TimerManager.h"

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

void AMixAmmo::HitTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

