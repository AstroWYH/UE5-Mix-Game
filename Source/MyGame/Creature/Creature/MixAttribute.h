// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MixAttribute.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API UMixAttribute : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxHealth;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Speed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 AttackVal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 DefenseVal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 AttackRange;

public:
	void ApplyHealth(int32 Val);

	void Death() const;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMixOnDeath);
	UPROPERTY(BlueprintAssignable)
	FMixOnDeath OnDeath;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMixOnApplyHealth, int32, ApplyVal, int32, Health, int32, MaxHealth);
	UPROPERTY(BlueprintAssignable)
	FMixOnApplyHealth OnApplyHealth;

};
