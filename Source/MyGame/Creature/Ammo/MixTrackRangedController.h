// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MixTrackRangedController.generated.h"

/**
 *
 */
UCLASS()
class MYGAME_API AMixTrackRangedController : public AAIController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	void OnPossess(APawn* InPawn) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<class AMixTrackRangedAmmo> TrackRangedAmmo;

public:
	bool bCanLaunch = false;

};
