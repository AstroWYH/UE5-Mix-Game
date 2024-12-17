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
	int32 MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMixCharacterHealthComponent")
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