// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI/MixUIPersistantInterface.h"
#include "UI/MixUISubsystemBase.h"
#include "MixUITestSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMixUITestSubsystem : public UMixUISubsystemBase
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

public:
	virtual void CreateUI() override;

public:
	virtual void BindUIEvent() override;

public:
	UFUNCTION()
	void TestAdd();

	UFUNCTION()
	void TestRemove();

private:
	UPROPERTY()
	TObjectPtr<class UUserWidget> TestBtnUI;
};