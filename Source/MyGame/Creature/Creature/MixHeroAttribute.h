// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MixAttribute.h"
#include "UObject/Object.h"
#include "MixHeroAttribute.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMixHeroAttribute : public UMixAttribute
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Magic;
};
