// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Creature/Creature/MixCreature.h"
#include "MixAttackComponent.generated.h"

class AMixAIController;
class AMixTrackRangedAmmo;
class AMixCreature;
struct FAIStimulus;

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

	UFUNCTION(BlueprintPure)
	static UMixAttackComponent* FindAttackComponent(const AMixCreature* Creature) { return (Creature ? Creature->FindComponentByClass<UMixAttackComponent>() : nullptr); }

public:
	void SetAttackRangeHidden(bool bHidden);

public:
	void PrepareAttack(const FVector& Pos);

	UFUNCTION(BlueprintCallable)
	void PrepareAttack(AMixCreature* Target);

	// HeroSelf
	AMixCreature* SelectTarget(const FVector& Pos);
	
	// HeroSelf
	AMixCreature* SelectClosestTarget(const FVector& Pos);

	void TurnToTarget(AMixCreature* Target);

	void TickTurnToTarget();

	void PerformRangedAttack();

	void PerformMeleeAttack();

	UFUNCTION(BlueprintCallable)
	void OnRangedMontageNofify();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	AMixCreature* Creature;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FGameplayTag AttackType;

public:
	FGameplayTag GetAttackType() const
	{
		return AttackType;
	}

	void SetAttackType(FGameplayTag InAttackType)
	{
		this->AttackType = InAttackType;
	}

private:
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

private:
	AMixAIController* AIController;
	
public:
	void OnAIControllerPostBeginPlay();

	UFUNCTION()
	void OnTargetInSightUpdate(AActor* Actor, FAIStimulus Stimulus);
};