// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "MixWorldSettings.generated.h"

/**
 *
 */
UCLASS()
class MYGAME_API AMixWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:

	AMixWorldSettings(const FObjectInitializer& ObjectInitializer);

public:
	// The default experience to use when a server opens this map if it is not overridden by the user-facing experience
	UPROPERTY(EditDefaultsOnly, Category = WorldSettings)
	TObjectPtr<class UMixUIAsset> UIAssets;

};
