#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Component/Attack/MixCharacterAttackComponent.h"

#include "MixBatmanAttackComponent.generated.h"

UCLASS()
class MYGAME_API UMixBatmanAttackComponent : public UMixCharacterAttackComponent
{
	GENERATED_BODY()

public:
	UMixBatmanAttackComponent();

	void BeginPlay() override;

public:
	void StopMovement() override;

	bool SelectTarget() override;

	void AttackSpawn() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMixHostAttackComponent")
	TWeakObjectPtr<class AMixBatman> Batman;
};