// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MixRangedAmmo.generated.h"

class AMixCreature;

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
	AMixCreature* Target;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	AMixCreature* Attacker;

private:
	struct FTimerHandle DestroyTimerHandle;

public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage();

	// 目前好像没用
	// UFUNCTION(BlueprintImplementableEvent)
	// void BP_HitTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void DestroySelf();

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	float DestroySelfTime = 2.0f;

public:
	UFUNCTION(BlueprintCallable)
	AMixCreature* GetTarget() const
	{
		return Target;
	}

	UFUNCTION(BlueprintCallable)
	void SetTarget(AMixCreature* InTarget)
	{
		Target = InTarget;
	}

	UFUNCTION(BlueprintCallable)
	AMixCreature* GetAttacker() const
	{
		return Attacker;
	}

	UFUNCTION(BlueprintCallable)
	void SetAttacker(AMixCreature* InAttacker)
	{
		Attacker = InAttacker;
	}

};
