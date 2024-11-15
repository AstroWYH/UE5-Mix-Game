#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character\MixCharacterAttackComponent.h"

#include "MixHostAttackComponent.generated.h"

UCLASS()
class MYGAME_API UMixHostAttackComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UMixHostAttackComponent(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/);

public:
    void BeginPlay() override;

    void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:    
     void Attack(FVector MouseClickPos);

     TWeakObjectPtr<class AMixBatman> SelectTarget();

     void PlayAttackMontage();

     UFUNCTION(BlueprintCallable, Category = "Host Attack Component")
     void AttackSpawn();

     void SetAttackRangeHidden(bool bHidden);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Host Attack Component")
    TWeakObjectPtr<class AMixHost> Host;

public:
    TArray<TWeakObjectPtr<class AMixBatman>> BatmanInRange;

    TWeakObjectPtr<class AMixBatman> SelectBatman;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Host Attack Component")
    float AttackRange = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Host Attack Component")
    bool bIsAttacking = false;

    FVector LastMouseClickPos;

    // Host旋转朝向敌方单位
    bool bIsRotating = false;
    FVector HostLocation;
    FRotator HostRotation;
    FVector TargetLocation;
    FRotator LookAtRotation;
    float TotalYawDifference = 0.0f;
    float KRotationTime = 0.3f;
    float YawPerFrame = 0.0f;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Host Attack Component")
	FSoftObjectPath AttackMontagePath{ TEXT("/Script/Engine.AnimMontage'/Game/MixGame/Character/Host/Animations/Primary_Fire_Med_Montage.Primary_Fire_Med_Montage'") };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Host Attack Component")
	FSoftObjectPath ArrowAmmoPath{ TEXT("/Script/Engine.Blueprint'/Game/MixGame/Ammo/HostAmmo/HostArrow.HostArrow_C'") };
};
