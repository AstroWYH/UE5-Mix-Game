// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MixRangedAmmo.generated.h"

UCLASS()
class MYGAME_API AMixRangedAmmo : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMixRangedAmmo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	AActor* Target;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	AActor* Shooter;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	int32 AttackVal = 0;

private:
	struct FTimerHandle DestroyTimerHandle;

public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_HitTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void DestroySelf();

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	float DestroySelfTime = 2.0f;

public:
	UFUNCTION(BlueprintCallable)
	AActor* GetTarget() const
	{
		return Target;
	}

	UFUNCTION(BlueprintCallable)
	void SetTarget(AActor* InTarget)
	{
		Target = InTarget;
	}

	UFUNCTION(BlueprintCallable)
	AActor* GetShooter() const
	{
		return Shooter;
	}

	UFUNCTION(BlueprintCallable)
	void SetShooter(AActor* InShooter)
	{
		Shooter = InShooter;
	}

	UFUNCTION(BlueprintCallable)
	int32 GetAttackVal() const
	{
		return AttackVal;
	}

};
