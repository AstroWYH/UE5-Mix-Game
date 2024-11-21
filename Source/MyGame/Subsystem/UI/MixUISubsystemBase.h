// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI/MixUIPersistantInterface.h"
#include "MixUISubsystemBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MYGAME_API UMixUISubsystemBase : public UGameInstanceSubsystem, public IMixUIPersistantInterface
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

public:
	virtual void CreatePersistantUI() override;
	
protected:
	virtual void LoadUIClass();

	virtual void BindUpdateUIEvent();

	virtual void BindUIEvent();

protected:
	FString UIModulePath;
};