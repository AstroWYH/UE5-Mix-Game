// Fill out your copyright notice in the Description page of Project Settings.


#include "MixUISubsystemBase.h"

void UMixUISubsystemBase::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	RegisterSelf();
	LoadUIClass();
	BindUpdateUIEvent();
}

void UMixUISubsystemBase::LoadUIClass()
{
}

void UMixUISubsystemBase::BindUpdateUIEvent()
{
}

void UMixUISubsystemBase::CreatePersistantUI()
{
	
}

void UMixUISubsystemBase::BindUIEvent()
{
}

void UMixUISubsystemBase::Deinitialize()
{
	UnRegisterSelf();

	Super::Deinitialize();
}