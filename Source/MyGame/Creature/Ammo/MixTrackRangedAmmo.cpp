// Fill out your copyright notice in the Description page of Project Settings.


#include "MixTrackRangedAmmo.h"

#include "GameFramework/FloatingPawnMovement.h"


// Sets default values
AMixTrackRangedAmmo::AMixTrackRangedAmmo()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

// Called when the game starts or when spawned
void AMixTrackRangedAmmo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMixTrackRangedAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMixTrackRangedAmmo::SetTrackController(AMixTrackRangedController* Controller)
{
	TrackRangedController = Controller;
}

