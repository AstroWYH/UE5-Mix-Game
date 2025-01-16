// Fill out your copyright notice in the Description page of Project Settings.

#include "MixAbilityMgr.h"

#include "GameplayTagContainer.h"
#include "MixAbilityBase.h"
#include "MixAssetManager.h"
#include "Creature/Controller/Hero/MixHostHeroControllerFix.h"
#include "Data/Ability/MixAbilityAsset.h"
#include "Level/MixLevelSubsystem.h"
#include "Utils/MixGameplayTags.h"
#include "Creature/Controller/MixHeroControllerFix.h"
#include "Creature/Creature/Hero/MixHero.h"

void UMixAbilityMgr::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	TickHandle = FTSTicker::GetCoreTicker().
		AddTicker(FTickerDelegate::CreateUObject(this, &UMixAbilityMgr::Tick), 0.0f);
}

void UMixAbilityMgr::Deinitialize()
{
	Super::Deinitialize();

	HeroAbilityData.Empty();
	FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
}

bool UMixAbilityMgr::Tick(float DeltaTime)
{
	TickTurnToMousePos();
	
	return true;
}

void UMixAbilityMgr::OnHeroSpawned()
{
	Super::OnHeroSpawned();
	
	UMixLevelSubsystem* LevelSubsystem = GetWorld()->GetSubsystem<UMixLevelSubsystem>();
	if (!ensure(LevelSubsystem)) return;
	
	const TArray<AMixHero*> Heros = LevelSubsystem->GetSpawnedHeros();
	for (AMixHero* EachHero : Heros)
	{
		// 准备英雄技能数据
		if (!ensure(EachHero)) continue;
		FMixAbilityData& HeroAbility = HeroAbilityData.FindOrAdd(EachHero);
		const UMixAbilityAsset& AbilityAsset = UMixAssetManager::Get().GetOrLoadAssetData<UMixAbilityAsset>(
			UMixAssetManager::Get().AbilityAsset);
		
		if (!(AbilityAsset.HeroAbilitys.Contains(EachHero->GetCreatureName()))) return;
		if (!(AbilityAsset.HeroAbilitys[EachHero->GetCreatureName()].Ability.Contains(MixGameplayTags::Ability_Type_Q))) return;
		
		TSubclassOf<AActor> BPAbilityClass_Q = AbilityAsset.HeroAbilitys[EachHero->GetCreatureName()].Ability[MixGameplayTags::Ability_Type_Q];
		AMixAbilityBase* Ability_Q = GetWorld()->SpawnActor<AMixAbilityBase>(BPAbilityClass_Q);
		Ability_Q->SetHero(EachHero);
		HeroAbility.Data.Add(MixGameplayTags::Ability_Type_Q, Ability_Q);
		// TODO: 其他WER也需要添加，整理成函数

		// 准备英雄朝向数据
		TurnData.Add(EachHero, FMixHeroTurnData());
	}
}

// TODO: 要考虑其他英雄
void UMixAbilityMgr::PrepareAbility(AMixHero* Hero, const FGameplayTag& AbilityKey, const FVector& AbilityPos)
{
	TurnData[Hero].Reset();
	Hero->GetController()->StopMovement();
	TurnToMousePos(Hero, AbilityKey, AbilityPos);
}

void UMixAbilityMgr::TurnToMousePos(AMixHero* Hero, const FGameplayTag& AbilityKey, const FVector& AbilityPos)
{
	if (!ensure(TurnData.Contains(Hero))) return;

	TurnData[Hero].CurAbilityKey = AbilityKey;
	
	TurnData[Hero].SelfLocation = Hero->GetActorLocation();
	TurnData[Hero].SelfRotation = FRotator(0.0f, Hero->GetActorRotation().Yaw, 0.0f);
	TurnData[Hero].TargetLocation = AbilityPos;
	TurnData[Hero].SelfLookAtRotation = FRotator(
		0.0f, (TurnData[Hero].TargetLocation - TurnData[Hero].SelfLocation).Rotation().
		                                                                    Yaw, 0.0f);

	TurnData[Hero].TotalYawDifference = FMath::Fmod(
		TurnData[Hero].SelfLookAtRotation.Yaw - TurnData[Hero].SelfRotation.Yaw + 180.0f, 360.0f) - 180.0f;
	TurnData[Hero].YawPerFrame = TurnData[Hero].TotalYawDifference / (TurnData[Hero].KRotationTime / GetWorld()->
		GetDeltaSeconds());

	TurnData[Hero].bNeedRotate = true;
}

void UMixAbilityMgr::TickTurnToMousePos()
{
	for (auto& [Hero, Data] : TurnData)
	{
		if (Data.bNeedRotate)
		{
			FRotator SelfNewRotation = FRotator(0.0f, Hero->GetActorRotation().Yaw + Data.YawPerFrame, 0.0f);
			Hero->SetActorRotation(SelfNewRotation);

			float RotationDiff = FMath::Abs(
				FMath::Fmod(Data.SelfLookAtRotation.Yaw - SelfNewRotation.Yaw + 180.0f, 360.0f) - 180.0f);
			// TODO: 参数配置
			if (RotationDiff <= 6.0f)
			{
				// 最后获取Hero最新应该的朝向，用于矫正
				FRotator FinalFixRotation = FRotator(
					0.0f, (Data.TargetLocation - Hero->GetActorLocation()).Rotation().Yaw,
					0.0f);
				Hero->SetActorRotation(FinalFixRotation);
				Data.bNeedRotate = false;

				// Bp_Ability蓝图具体执行自己的逻辑
				AMixAbilityBase* Ability = HeroAbilityData[Hero].Data[Data.CurAbilityKey];
				Ability->BP_PerformAbility();
			}
		}
	}
}

// TODO: 注意技能之间需要间隔拦截，否则连续按，CurAbilityKey可能出问题
void UMixAbilityMgr::OnMontageNoify(AMixHero* Hero)
{
	AMixAbilityBase* Ability = HeroAbilityData[Hero].Data[TurnData[Hero].CurAbilityKey];
	Ability->BP_OnMontageNotify(TurnData[Hero].TargetLocation);
}