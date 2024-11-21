// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/DataTable.h"

#include "MixDataSubsystem.generated.h"

UCLASS()
class MYGAME_API UMixDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	template <typename T>
	TArray<T*> LoadDataTableFromPath(const FString& Path, const FString& Context)
	{
		UDataTable* DataTable = LoadObject<UDataTable>(nullptr, *Path);
		if (!ensure(DataTable)) return TArray<T*>();

		TArray<T*> AllDataCfg;
		DataTable->GetAllRows<T>(Context, AllDataCfg);

		return AllDataCfg;
	}

};