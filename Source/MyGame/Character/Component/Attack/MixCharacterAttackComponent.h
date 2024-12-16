#pragma once

#include "CoreMinimal.h"
#include "Component/MixCharacterComponent.h"
#include "Components/ActorComponent.h"
#include "MixCharacterAttackComponent.generated.h"

UCLASS()
class MYGAME_API UMixCharacterAttackComponent : public UMixCharacterComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "UMixCharacterAttackComponent")
	virtual void PreAttack();

	virtual void StopMovement();

	virtual bool SelectTarget();

	virtual void TurnToTarget();

	virtual void TickRotateToTarget();

	virtual void PlayAttackMontage();

	UFUNCTION(BlueprintCallable, Category = "UMixCharacterAttackComponent")
	virtual void AttackSpawn();

public:
	TWeakObjectPtr<class AMixCharacter> SelectCharacterTarget;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMixCharacterAttackComponent")
	float AttackRange = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMixCharacterAttackComponent")
	bool bIsAttacking = false;

	// 朝向目标参数
	FVector SelfLocation;
	FRotator SelfRotation;
	FVector TargetLocation;
	FRotator SelfLookAtRotation;
	float TotalYawDifference = 0.0f;
	bool bIsRotating = false;
	float KRotationTime = 0.0f;
	float YawPerFrame = 0.0f;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMixCharacterAttackComponent")
	FSoftObjectPath AttackMontagePath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMixCharacterAttackComponent")
	FSoftObjectPath AmmoPath;
};