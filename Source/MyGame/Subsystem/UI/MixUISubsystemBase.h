// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI/MixUIPersistantInterface.h"
#include "UI/MixUIMgr.h"
#include "MixUIAsset.h"
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
	virtual void LoadUIClass() override;

	virtual void CreateUI() override;

	virtual void BindUIEvent() override;

};