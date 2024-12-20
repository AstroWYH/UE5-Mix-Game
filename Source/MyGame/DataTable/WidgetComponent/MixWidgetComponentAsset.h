// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MixWidgetComponentAsset.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMixWidgetComponentAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "HeadUI")
	TMap<FName, TSubclassOf<UUserWidget>> Classes;

};
