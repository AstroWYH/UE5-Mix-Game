#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character\MixCharacterAttackComponent.h"
#include "Engine\TimerHandle.h"

#include "MixHostAttackComponent.generated.h"

UCLASS()
class MYGAME_API UMixHostAttackComponent : public UMixCharacterAttackComponent
{
    GENERATED_BODY()

public:
    UMixHostAttackComponent();

    void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:    
     void Attack(FVector MouseClickPos) override;

public:
    TArray<TWeakObjectPtr<class AMixBatman>> BatmanInRange;

    TWeakObjectPtr<class AMixBatman> SelectTarget();

    TWeakObjectPtr<class AMixBatman> SelectBatman;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Host Attack Component")
    float AttackRange = 500.0f;

    FVector LastMouseClickPos;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Host Attack Component")
    bool bIsAttacking = false;

    FTimerHandle RotationHandle;

    bool bIsRotating = false;

    FVector HostLocation;
    FRotator HostRotation;
    FVector TargetLocation;
    FRotator TargetRotation;

};
