// Fill out your copyright notice in the Description page of Project Settings.

#include "MixAbilityMgr.h"

#include "GameplayTagContainer.h"
#include "MixAbilityBase.h"
#include "MixAssetManager.h"
#include "Creature/Controller/Hero/MixHostHeroController.h"
#include "Data/Ability/MixAbilityAsset.h"
#include "Level/MixLevelSubsystem.h"
#include "MixGameplayTags.h"
#include "Creature/Controller/MixHeroController.h"
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
		// ׼��Ӣ�ۼ�������
		if (!ensure(EachHero)) continue;
		FMixAbilityData& HeroAbility = HeroAbilityData.FindOrAdd(EachHero);
		const UMixAbilityAsset& AbilityAsset = UMixAssetManager::Get().GetOrLoadAssetData<UMixAbilityAsset>(
			UMixAssetManager::Get().AbilityAsset);
		
		if (!ensure(AbilityAsset.HeroAbilitys.Contains(EachHero->GetHeroName()))) return;
		if (!ensure(AbilityAsset.HeroAbilitys[EachHero->GetHeroName()].Ability.Contains(MixGameplayTags::Ability_Type_Q))) return;
		
		TSubclassOf<AActor> BPAbilityClass_Q = AbilityAsset.HeroAbilitys[EachHero->GetHeroName()].Ability[MixGameplayTags::Ability_Type_Q];
		AMixAbilityBase* Ability_Q = GetWorld()->SpawnActor<AMixAbilityBase>(BPAbilityClass_Q);
		Ability_Q->SetHero(EachHero);
		HeroAbility.Data.Add(MixGameplayTags::Ability_Type_Q, Ability_Q);
		// TODO: ����WERҲ��Ҫ��ӣ�����ɺ���

		// ׼��Ӣ�۳�������
		TurnData.Add(EachHero, FMixHeroTurnData());
	}
}

// TODO: Ҫ��������Ӣ��
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
			// TODO: ��������
			if (RotationDiff <= 6.0f)
			{
				// ����ȡHero����Ӧ�õĳ������ڽ���
				FRotator FinalFixRotation = FRotator(
					0.0f, (Data.TargetLocation - Hero->GetActorLocation()).Rotation().Yaw,
					0.0f);
				Hero->SetActorRotation(FinalFixRotation);
				Data.bNeedRotate = false;

				// Bp_Ability��ͼ����ִ���Լ����߼�
				AMixAbilityBase* Ability = HeroAbilityData[Hero].Data[Data.CurAbilityKey];
				Ability->BP_PerformAbility();
			}
		}
	}
}

// TODO: �ع�; ע�⼼��֮����Ҫ������أ�������������CurAbilityKey���ܳ�����
void UMixAbilityMgr::OnMontageNoify(AMixHero* Hero)
{
	AMixAbilityBase* Ability = HeroAbilityData[Hero].Data[TurnData[Hero].CurAbilityKey];
	Ability->BP_OnMontageNotify(TurnData[Hero].TargetLocation);
}