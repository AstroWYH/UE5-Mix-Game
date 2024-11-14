// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo/MixAIAmmoController.h"
#include "Ammo\Host\MixHostAmmo.h"

void AMixAIAmmoController::BeginPlay()
{
	Super::BeginPlay();

	// ��ʱ�޷���ȡPawn����ΪSpawnActor<AMixAIAmmoController>�Ĺ����У���ִ��AMixAIAmmoController::BeginPlay()
	// ����ʱ��ûOnPossess(Pawn)
}

void AMixAIAmmoController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

	Ammo = Cast<AMixHostAmmo>(GetPawn());
	if (!ensure(Ammo.IsValid())) return;
	if (!ensure(Ammo->Target.IsValid())) return;

	// Ammo->Target�������CustomPreSpawnInitalization���ã���˴���ȡ����
	 MoveToActor(Ammo->Target.Get(), 5.0f);

// 	FVector TargetLocation = Ammo->Target->GetActorLocation();
// 	TargetLocation.Z += 50.0f;
// 	MoveToLocation(TargetLocation, 5.0f);
}
