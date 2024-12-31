// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MixUIAsset.generated.h"

USTRUCT(BlueprintType)
struct FUIClassArray
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TMap<FName, TSubclassOf<UUserWidget>> UIClasses;
};

UCLASS()
class MYGAME_API UMixUIAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	const TMap<FName, FUIClassArray>& GetAllUIAssets() const
	{
		return AllUIAssets;
	}
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TMap<FName, FUIClassArray> AllUIAssets;
};
