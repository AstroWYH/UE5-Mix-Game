// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MixUIMgrSubsystem.generated.h"

UCLASS()
class MYGAME_API UMixUIMgrSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	void PostInit();

public:
	UClass* LoadUIClass(const FString& ModulePath, const FString& BlueprintName);

	void CreatePersistantUI();

};