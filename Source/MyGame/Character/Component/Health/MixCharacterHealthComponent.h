#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MixCharacterHealthComponent.generated.h"

UCLASS()
class MYGAME_API UMixCharacterHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMixCharacterHealthComponent")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UMixCharacterHealthComponent")
	float CurrentHealth;

public:
	virtual void TakeDamage(int32 DamageVal);

	virtual void Death();

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMixOnCharacterDeath);

	UPROPERTY(BlueprintAssignable)
	FMixOnCharacterDeath OnCharacterDeath;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMixOnCharacterTakeDamage, int32, DamageVal);

	UPROPERTY(BlueprintAssignable)
	FMixOnCharacterTakeDamage OnCharacterTakeDamage;
};