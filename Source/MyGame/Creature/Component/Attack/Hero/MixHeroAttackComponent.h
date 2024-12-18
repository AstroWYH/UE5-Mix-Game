#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Creature/Component/Attack/MixCreatureAttackComponent.h"

#include "MixHeroAttackComponent.generated.h"

UCLASS()
class MYGAME_API UMixHeroAttackComponent : public UMixCreatureAttackComponent
{
    GENERATED_BODY()

public:
    UMixHeroAttackComponent();

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMixHeroAttackComponent")
    TWeakObjectPtr<class AMixHero> Host;

public:
    TArray<TWeakObjectPtr<class AMixBatman>> BatmanInRange;

    FVector LastMouseClickPos;

};
