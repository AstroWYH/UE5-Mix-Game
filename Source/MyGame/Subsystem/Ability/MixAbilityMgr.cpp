// Fill out your copyright notice in the Description page of Project Settings.

#include "MixAbilityMgr.h"

#include "GameplayTagContainer.h"
#include "MixAbilityBase.h"
#include "MixAssetManager.h"
#include "Creature/Controller/Hero/MixHeroController.h"
#include "Data/Ability/MixAbilityAsset.h"
#include "Level/MixLevelSubsystem.h"
#include "MixGameplayTags.h"
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
		if (!ensure(EachHero)) continue;
		FMixAbilityData& HeroAbility = HeroAbilityData.FindOrAdd(EachHero->GetHeroName());
		const UMixAbilityAsset& AbilityAsset = UMixAssetManager::Get().GetAsset_Ability();
		
		if (!ensure(AbilityAsset.HeroAbilitys.Contains(EachHero->GetHeroName()))) return;
		if (!ensure(AbilityAsset.HeroAbilitys[EachHero->GetHeroName()].Ability.Contains(MixGameplayTags::Ability_Type_Q))) return;
		
		TSubclassOf<AActor> BPAbilityClass_Q = AbilityAsset.HeroAbilitys[EachHero->GetHeroName()].Ability[MixGameplayTags::Ability_Type_Q];
		AMixAbilityBase* Ability_Q = GetWorld()->SpawnActor<AMixAbilityBase>(BPAbilityClass_Q);
		Ability_Q->SetHero(EachHero);
		HeroAbility.Data.Add(MixGameplayTags::Ability_Type_Q, Ability_Q);
		// TODO: WERҲ��Ҫ���
	}
}

// TODO: ����Ҫ��������Ӣ�ۣ�InAbilityMouseLocation��ø�ΪInAbilityPos
void UMixAbilityMgr::PrepareAbility(AMixHero* InHero, FGameplayTag AbilityKey, FVector InAbilityPos)
{
	CurAbilityKey = AbilityKey;
	Hero = InHero;
	AbilityMouseLocation = InAbilityPos;
	StopMovement();
	TurnToMousePos();
}

// TODO: ����Hero�϶�����AMixHeroController�������ⷽ��Ҫ��һ��
void UMixAbilityMgr::StopMovement()
{
	AMixHeroController* HeroController = Cast<AMixHeroController>(Hero->GetController());
	if (!ensure(HeroController))
		return;
	
	HeroController->StopMovement();
}

void UMixAbilityMgr::TurnToMousePos()
{
	AMixHeroController* HeroController = Cast<AMixHeroController>(Hero->GetController());
	if (!ensure(HeroController)) return;

	// ����Ŀ����ת
	SelfLocation = Hero->GetActorLocation();
	SelfRotation = FRotator(0.0f, Hero->GetActorRotation().Yaw, 0.0f);
	// TODO: ���λ�ÿ��������Ǻ�׼Ŀǰ
	TargetLocation = HeroController->GetMouseClickFloorPosition();
	SelfLookAtRotation = FRotator(0.0f, (TargetLocation - SelfLocation).Rotation().Yaw, 0.0f);

	// ����ȷ�����ǶȽ�С�ķ�����ת
	TotalYawDifference = FMath::Fmod(SelfLookAtRotation.Yaw - SelfRotation.Yaw + 180.0f, 360.0f) - 180.0f;
	YawPerFrame = TotalYawDifference / (KRotationTime / GetWorld()->GetDeltaSeconds());

	// �ÿ�ʼת��״̬
	bIsRotating = true;
}

void UMixAbilityMgr::TickTurnToMousePos()
{
	if (bIsRotating)
	{
		FRotator SelfNewRotation = FRotator(0.0f, Hero->GetActorRotation().Yaw + YawPerFrame, 0.0f);
		Hero->SetActorRotation(SelfNewRotation);

		float RotationDiff = FMath::Abs(
			FMath::Fmod(SelfLookAtRotation.Yaw - SelfNewRotation.Yaw + 180.0f, 360.0f) - 180.0f);
		// TODO: ��������
		if (RotationDiff <= 6.0f)
		{
			// ����ȡHero����Ӧ�õĳ������ڽ���
			FRotator FinalFixRotation = FRotator(
				0.0f, (TargetLocation - Hero->GetActorLocation()).Rotation().Yaw,
				0.0f);
			Hero->SetActorRotation(FinalFixRotation);
			bIsRotating = false;

			// ��¼����ʩ�������λ��
			AMixHeroController* HeroController = Cast<AMixHeroController>(Hero->GetController());
			if (!ensure(HeroController)) return;

			// Bp_Ability��ͼ����ִ���Լ����߼�
			AMixAbilityBase* Ability = HeroAbilityData[Hero->GetHeroName()].Data[CurAbilityKey];
			Ability->BP_PerformAbility();
		}
	}
}

void UMixAbilityMgr::OnMontageNoify()
{
	AMixAbilityBase* Ability = HeroAbilityData[Hero->GetHeroName()].Data[CurAbilityKey];
	Ability->BP_OnMontageNotify(AbilityMouseLocation);
}