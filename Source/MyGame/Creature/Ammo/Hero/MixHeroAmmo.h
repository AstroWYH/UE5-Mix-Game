// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Creature/Ammo/MixAmmo.h"
#include "MixHeroAmmo.generated.h"

UCLASS()
class MYGAME_API AMixHeroAmmo : public AMixAmmo
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMixHeroAmmo();

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void HitTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	               int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};