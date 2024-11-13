// Fill out your copyright notice in the Description page of Project Settings.


#include "MixHostAmmo.h"
#include "GameFramework\ProjectileMovementComponent.h"

// Sets default values
AMixHostAmmo::AMixHostAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AMixHostAmmo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMixHostAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

