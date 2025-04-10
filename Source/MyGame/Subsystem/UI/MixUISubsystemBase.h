// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MixGameSubsystem.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI/MixUIPersistantInterface.h"
#include "UI/MixUIMgr.h"
#include "Data/UI/MixUIAsset.h"
#include "MixUISubsystemBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MYGAME_API UMixUISubsystemBase : public UMixGameSubsystem, public IMixUIPersistantInterface
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

public:
	virtual void OnHeroSpawned() override;

public:
	virtual void CreateUI() override;

	virtual void BindUIEvent() override;

protected:
	TWeakObjectPtr<UMixUIMgr> UIMgr;

	UPROPERTY()
	TMap<FName, UObject*> BPUIProps;

};