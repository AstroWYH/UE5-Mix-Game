// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MixUISubsystem.generated.h"

/**
 * 该类暂时不起作用
 */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API UMixUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    void Initialize(FSubsystemCollectionBase& Collection) override;

    void Deinitialize() override;

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void BpInitialize();

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void BpDeInitialize();

public:
/*
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void UpdateInventory();*/

};