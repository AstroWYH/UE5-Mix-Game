// Fill out your copyright notice in the Description page of Project Settings.


#include "MixNoTrackRangedAmmo.h"


// Sets default values
AMixNoTrackRangedAmmo::AMixNoTrackRangedAmmo()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMixNoTrackRangedAmmo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMixNoTrackRangedAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


