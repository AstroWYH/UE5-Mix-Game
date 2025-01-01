// Fill out your copyright notice in the Description page of Project Settings.

#include "MixAbilityMgr.h"

#include "GameplayTagContainer.h"
#include "MixAbilityBase.h"
#include "MixAssetManager.h"
#include "Creature/Controller/Hero/MixHeroController.h"
#include "DataAsset/Ability/MixAbilityAsset.h"
#include "Level/MixLevelSubsystem.h"
#include "MixGameplayTags.h"

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
	return true;
}

void UMixAbilityMgr::OnHeroSpawned()
{
	Super::OnHeroSpawned();
	UMixLevelSubsystem* LevelSubsystem = GetWorld()->GetSubsystem<UMixLevelSubsystem>();
	if (!ensure(LevelSubsystem)) return;
	
	const TArray<AMixHero*> Heros = LevelSubsystem->GetSpawnedHeros();
	for (const AMixHero* Hero : Heros)
	{
		if (!ensure(Hero)) continue;
		FMixAbilityData& HeroAbility = HeroAbilityData.FindOrAdd(Hero->GetHeroName());
		const UMixAbilityAsset& AbilityAsset = UMixAssetManager::Get().GetAsset_Ability();
		
		if (!ensure(AbilityAsset.HeroAbilitys.Contains(Hero->GetHeroName()))) return;
		if (!ensure(AbilityAsset.HeroAbilitys[Hero->GetHeroName()].Ability.Contains(MixGameplayTags::Ability_Type_Q))) return;
		
		TSubclassOf<AActor> BPAbilityClass_Q = AbilityAsset.HeroAbilitys[Hero->GetHeroName()].Ability[MixGameplayTags::Ability_Type_Q];
		AMixAbilityBase* Ability_Q = GetWorld()->SpawnActor<AMixAbilityBase>(BPAbilityClass_Q);
		HeroAbility.Data.Add(MixGameplayTags::Ability_Type_Q, Ability_Q);
		// TODO: WER也需要添加
	}
}

void UMixAbilityMgr::PerformAbility(FGameplayTag HeroName, FGameplayTag AbilityKey)
{
	StopMovement();
	TurnToMousePos();
}

void UMixAbilityMgr::StopMovement()
{
	// AMixHeroController* HeroController = Cast<AMixHeroController>(Hero->GetController());
	// if (!ensure(HeroController))
	// 	return;
	//
	// HeroController->StopMovement();
}

void UMixAbilityMgr::TurnToMousePos()
{

}

void UMixAbilityMgr::TickTurnToMousePos()
{

}