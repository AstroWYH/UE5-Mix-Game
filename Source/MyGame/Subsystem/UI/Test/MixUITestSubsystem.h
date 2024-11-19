// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI/MixUIPersistantInterface.h"
#include "MixUITestSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMixUITestSubsystem : public UGameInstanceSubsystem, public IMixUIPersistantInterface
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;
	
public:
	virtual void CreateUI() override;

public:
	UFUNCTION()
	void TestAdd();

	UFUNCTION()
	void TestRemove();

private:
	UPROPERTY()
	UClass* BpTestUIClass = nullptr;

	UPROPERTY()
	TObjectPtr<class UMixTestBtnWidget> TestBtnUI;

};