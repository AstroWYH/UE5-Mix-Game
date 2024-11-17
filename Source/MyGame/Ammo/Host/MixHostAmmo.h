// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ammo/MixAmmo.h"
#include "MixHostAmmo.generated.h"

UCLASS()
class MYGAME_API AMixHostAmmo : public AMixAmmo
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMixHostAmmo();

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void HitTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
