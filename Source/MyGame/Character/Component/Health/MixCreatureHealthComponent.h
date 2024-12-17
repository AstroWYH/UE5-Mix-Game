#pragma once

#include "CoreMinimal.h"
#include "Component/MixCreatureComponent.h"
#include "Components/ActorComponent.h"
#include "MixCreatureHealthComponent.generated.h"

UCLASS()
class MYGAME_API UMixCreatureHealthComponent : public UMixCreatureComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMixCreatureHealthComponent")
	int32 MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMixCreatureHealthComponent")
	int32 CurHealth = 100.0f;

public:
	virtual void TakeDamage(int32 DamageVal);

	virtual void Death();

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMixOnCharacterDeath);
	UPROPERTY(BlueprintAssignable)
	FMixOnCharacterDeath OnCharacterDeath;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMixOnCharacterTakeDamage, int32, DamageVal, int32, HealthVal, int32, MaxHealthVal);
	UPROPERTY(BlueprintAssignable)
	FMixOnCharacterTakeDamage OnCharacterTakeDamage;
};