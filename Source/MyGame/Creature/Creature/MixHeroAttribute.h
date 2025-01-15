// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MixAttribute.h"
#include "UObject/Object.h"
#include "MixHeroAttribute.generated.h"

class AMixHeroControllerFix;
/**
 * 
 */
UCLASS()
class MYGAME_API UMixHeroAttribute : public UMixAttribute
{
	GENERATED_BODY()

public:
	virtual void InitChildAttributes(AMixCreature* Creature, const UDataTable* AttributeDT, const FMixHeroAttributeData* AttributeData) override
	{
		Magic = AttributeData->MaxMagic;
	}

	virtual void ApplyHealth(AMixCreature* Attacker, int32 Val) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Magic;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxMagic;
};
