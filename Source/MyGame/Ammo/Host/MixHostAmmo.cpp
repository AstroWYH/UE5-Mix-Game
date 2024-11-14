// Fill out your copyright notice in the Description page of Project Settings.


#include "MixHostAmmo.h"
#include "GameFramework\FloatingPawnMovement.h"
#include "TimerManager.h"

// Sets default values
AMixHostAmmo::AMixHostAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

// Called when the game starts or when spawned
void AMixHostAmmo::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, [this]()
		{
			Destroy();
		}, 10.0f, false);
}

// Called every frame
void AMixHostAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

