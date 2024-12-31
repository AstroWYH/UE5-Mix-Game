// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MixTickGameInstanceSubsystem.generated.h"

UCLASS()
class MYGAME_API UMixTickGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

protected:
	virtual bool Tick(float DeltaTime);

private:
	FTSTicker::FDelegateHandle TickHandle;
};
