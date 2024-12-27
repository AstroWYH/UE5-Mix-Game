// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MixRangedAmmo.h"
#include "GameFramework/Pawn.h"
#include "MixNoTrackRangedAmmo.generated.h"

UCLASS()
class MYGAME_API AMixNoTrackRangedAmmo : public AMixRangedAmmo
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMixNoTrackRangedAmmo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
