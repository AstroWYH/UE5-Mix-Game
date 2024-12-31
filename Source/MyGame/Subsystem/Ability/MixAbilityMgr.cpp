// Fill out your copyright notice in the Description page of Project Settings.

#include "MixAbilityMgr.h"

#include "GameplayTagContainer.h"
#include "MixAbilityBase.h"
#include "Creature/Controller/Hero/MixHeroController.h"
#include "Level/MixLevelSubsystem.h"

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
		TMap<FGameplayTag, AMixAbilityBase*>& HeroAbility = HeroAbilityData.FindOrAdd(Hero->GetHeroName());
		// TODO: ≈‰÷√µΩAssetMgr
		TSubclassOf<AMixAbilityBase> BPAbilityClass;
		AMixAbilityBase* Ability = GetWorld()->SpawnActor<AMixAbilityBase>(BPAbilityClass);
		HeroAbility.Add(MixGameplayTags::Ability_Type_Q, Ability);
	}
}

void UMixAbilityMgr::PerformAbility(FGameplayTag HeroName, FGameplayTag AbilityKey)
{
	StopMovement();
	TurnToMousePos();
}

void UMixAbilityMgr::StopMovement()
{
	AMixHeroController* HeroController = Cast<AMixHeroController>(Hero->GetController());
	if (!ensure(HeroController))
		return;

	HeroController->StopMovement();
}

void UMixAbilityMgr::TurnToMousePos()
{

}

void UMixAbilityMgr::TickTurnToMousePos()
{

}