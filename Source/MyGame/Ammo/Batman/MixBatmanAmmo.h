// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ammo/MixAmmo.h"
#include "MixBatmanAmmo.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API AMixBatmanAmmo : public AMixAmmo
{
	GENERATED_BODY()
	
public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
