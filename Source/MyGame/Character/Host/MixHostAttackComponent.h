#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character\MixCharacterAttackComponent.h"

#include "MixHostAttackComponent.generated.h"

UCLASS()
class MYGAME_API UMixHostAttackComponent : public UMixCharacterAttackComponent
{
    GENERATED_BODY()

public:
    UMixHostAttackComponent();

    void BeginPlay() override;

    void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:    
	void StopMovement() override;

	void SelectTarget() override;

public:
	TWeakObjectPtr<class AMixBatman> SelectClosestTarget();

	void PlayAttackMontage();

	UFUNCTION(BlueprintCallable, Category = "UMixHostAttackComponent")
	void AttackSpawn();

	void SetAttackRangeHidden(bool bHidden);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMixHostAttackComponent")
    TWeakObjectPtr<class AMixHost> Host;

public:
    TArray<TWeakObjectPtr<class AMixBatman>> BatmanInRange;

    FVector LastMouseClickPos;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMixHostAttackComponent")
	FSoftObjectPath AttackMontagePath{ TEXT("/Script/Engine.AnimMontage'/Game/MixGame/Character/Host/Animations/Primary_Fire_Med_Montage.Primary_Fire_Med_Montage'") };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMixHostAttackComponent")
	FSoftObjectPath ArrowAmmoPath{ TEXT("/Script/Engine.Blueprint'/Game/MixGame/Ammo/HostAmmo/HostArrow.HostArrow_C'") };
};
