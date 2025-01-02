// Fill out your copyright notice in the Description page of Project Settings.


#include "MixUISubsystemBase.h"

#include "Data/UI/MixUIAsset.h"
#include "MixUIMgr.h"

void UMixUISubsystemBase::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// 注册所有的UISubsystem，用于UIMgr统一管理
	RegisterSelf();

	UIMgr = Collection.InitializeDependency<UMixUIMgr>();
}

void UMixUISubsystemBase::CreateUI()
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
