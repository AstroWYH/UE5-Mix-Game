#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MixCharacterAttackComponent.generated.h"

UCLASS()
class MYGAME_API UMixCharacterAttackComponent : public UActorComponent
{
    GENERATED_BODY()
    
public:
    virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "UMixCharacterAttackComponent")
	virtual void PreAttack();

    UFUNCTION(BlueprintCallable, Category = "UMixCharacterAttackComponent")
	virtual void StopMovement();

	UFUNCTION(BlueprintCallable, Category = "UMixCharacterAttackComponent")
	virtual void SelectTarget();

	UFUNCTION(BlueprintCallable, Category = "UMixCharacterAttackComponent")
	virtual void TurnToTarget();

public:
	TWeakObjectPtr<class AMixCharacter> MixCharacter;

    TWeakObjectPtr<class AMixCharacter> SelectCharacterTarget;

public:
    // 攻击参数
    int32 AttackVal = 0;

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

};
