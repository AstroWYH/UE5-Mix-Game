// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MixRangedAmmo.h"
#include "GameFramework/Pawn.h"
#include "MixTrackRangedAmmo.generated.h"

class AMixTrackRangedController;

UCLASS()
class MYGAME_API AMixTrackRangedAmmo : public AMixRangedAmmo
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMixTrackRangedAmmo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetTrackController(AMixTrackRangedController* InController);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AMixTrackRangedController* TrackRangedController;

public:
	// AI Controller使用MoveTo时，需要NavXXXMovementComponent，否则也无法移动
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UFloatingPawnMovement> FloatingPawnMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AmmoOffset = 0;
};
