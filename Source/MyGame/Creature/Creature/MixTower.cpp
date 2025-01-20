// Fill out your copyright notice in the Description page of Project Settings.


#include "MixTower.h"

#include "UI/HeadUI/MixHeadUIWidget.h"


// Sets default values
AMixTower::AMixTower()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMixTower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMixTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMixTower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMixTower::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();

	// HeadUI->SetDesiredSizeInViewport(FVector2d(200.0f, 200.0f));
}

