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

	bool SelectTarget() override;

	void AttackSpawn() override;

public:
	TWeakObjectPtr<class AMixBatman> SelectClosestTarget();

	void SetAttackRangeHidden(bool bHidden);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMixHostAttackComponent")
    TWeakObjectPtr<class AMixHost> Host;

public:
    TArray<TWeakObjectPtr<class AMixBatman>> BatmanInRange;

    FVector LastMouseClickPos;

};
