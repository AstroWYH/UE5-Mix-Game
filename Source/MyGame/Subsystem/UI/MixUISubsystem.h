// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MixUISubsystem.generated.h"

/**
 * 该类暂时不起作用
 */
UCLASS()
class MYGAME_API UMixUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void Initialize(FSubsystemCollectionBase& Collection) override;

	void Deinitialize() override;

public:
	UClass* LoadUIResource(const TCHAR* Path);

	void CreatePersistantUI();

};