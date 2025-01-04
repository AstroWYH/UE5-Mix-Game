// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "MixAttackComponent.generated.h"


class AMixTrackRangedAmmo;
class AMixCreature;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYGAME_API UMixAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMixAttackComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SetAttackRangeHidden(bool bHidden);

public:
	void PrepareAttack(const FVector& Pos);

	UFUNCTION(BlueprintCallable)
	void PrepareAttack(AMixCreature* Target);

	// 仅对于HeroSelf
	AMixCreature* SelectTarget(const FVector& Pos);
	
	// 仅对于HeroSelf
	AMixCreature* SelectClosestTarget(const FVector& Pos);

	void TurnToTarget(AMixCreature* Target);

	void TickTurnToTarget();

	void PerformRangedAttack();

	void PerformMeleeAttack();

	UFUNCTION(BlueprintCallable)
	void OnMontageNofify();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AMixCreature* Creature;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsRanged = false;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AMixTrackRangedAmmo> AmmoClass;

private:
	// 朝向目标参数
	FVector SelfLocation;
	FRotator SelfRotation;
	FVector TargetLocation;
	FRotator SelfLookAtRotation;
	float TotalYawDifference = 0.0f;
	bool bIsRotating = false;
	float YawPerFrame = 0.0f;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float KRotationTime = 0.3f;

	TArray<AMixCreature*> CreaturesInRange;
	AMixCreature* TargetCreature;

public:
	void SetIsRotating(bool bInIsRotating)
	{
		this->bIsRotating = bInIsRotating;
	}

public:
	AMixCreature* GetCreature() const
	{
		return Creature;
	}

	void SetCreature(AMixCreature* InCreature)
	{
		this->Creature = InCreature;
	}
};