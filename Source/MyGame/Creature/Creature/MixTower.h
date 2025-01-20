// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MixCreature.h"
#include "MixTower.generated.h"

UCLASS()
class MYGAME_API AMixTower : public AMixCreature
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMixTower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};