// Fill out your copyright notice in the Description page of Project Settings.


#include "MixTickGameInstanceSubsystem.h"

void UMixTickGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	TickHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UMixTickGameInstanceSubsystem::Tick), 0.0f);
}

void UMixTickGameInstanceSubsystem::Deinitialize()
{
	Super::Deinitialize();

	FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
}

bool UMixTickGameInstanceSubsystem::Tick(float DeltaTime)
{
	return true;
}
