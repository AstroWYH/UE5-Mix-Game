// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MixAIAmmoController.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API AMixAIAmmoController : public AAIController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	void OnPossess(APawn* InPawn) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Host Controller")
	TWeakObjectPtr<class AMixHostAmmo> Ammo;

public:
	bool bCanLaunch = false;

};
