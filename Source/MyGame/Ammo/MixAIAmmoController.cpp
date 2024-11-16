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
	// ʹ��MoveToActor�޷��͵з���λ������ײ
	// MoveToActor(Ammo->Target.Get(), 0.0f);
	bCanLaunch = true;

}

void AMixAIAmmoController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanLaunch)
	{
		FVector TargetLocation = Ammo->Target->GetActorLocation();
		MoveToLocation(TargetLocation, 1.0f);
	}
}
