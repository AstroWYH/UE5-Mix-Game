// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MixAttribute.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMixAttribute : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Speed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 AttackVal;
};
