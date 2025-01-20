// Fill out your copyright notice in the Description page of Project Settings.


#include "MixLevelSubsystem.h"

#include "MixAssetManager.h"
#include "MixGameSubsystem.h"
#include "Ability/MixAbilityMgr.h"
#include "Components/CapsuleComponent.h"
#include "Creature/Component/MixAttackComponent.h"
#include "Creature/Controller/MixHeroControllerFix.h"
#include "Creature/Controller/Hero/MixHostHeroControllerFix.h"
#include "Creature/Creature/MixAttribute.h"
#include "Creature/Creature/MixHeroAttribute.h"
#include "Creature/Creature/Batman/MixBatman.h"
#include "Creature/Creature/Hero/MixHero.h"
#include "Data/Attribute/MixAttributeData.h"
#include "Data/Attribute/MixHeroAttributeData.h"
#include "Game/MixGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HeadUI/MixHeadUIWidget.h"

void UMixLevelSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UMixLevelSubsystem::Deinitialize()
{
	Super::Deinitialize();

	SpawnedHeros.Empty();
	SpawnedBatmans.Empty();
}

void UMixLevelSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	if (!(InWorld.GetName() == "LOL")) return;

	GenerateHeros();

	// 通知GameMgr->OnHeroSpawned
	TArray<UMixGameSubsystem*> GameSubsystems = InWorld.GetGameInstance()->GetSubsystemArray<UMixGameSubsystem>();
	for (UMixGameSubsystem* GameSubsystem : GameSubsystems)
	{
		if (!ensure(GameSubsystem)) continue;
		GameSubsystem->OnHeroSpawned();
	}
	
	GenerateBatmans();
}

void UMixLevelSubsystem::GenerateHeros()
{
	// 生成HeroSelf Ashe
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AActor::StaticClass(), "HeroSpawnPoint_Ashe", OutActors);
		if (!ensure(OutActors.IsValidIndex(0))) return;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FTransform SpawnTransform = OutActors[0]->GetActorTransform();
		AMixHero* Hero = GetWorld()->SpawnActor<AMixHero>(UMixAssetManager::Get().HeroModelInfo[MixGameplayTags::Creature_Name_Ashe].Class, SpawnTransform, SpawnParams);
		if (!ensure(Hero)) return;
		SpawnedHeros.AddUnique(Hero);
		Hero->SetCreatureName(MixGameplayTags::Creature_Name_Ashe);
		Hero->SetCreatureType(MixGameplayTags::Creature_Type_Hero);
		Hero->SetCreatureCamp(MixGameplayTags::Creature_Camp_Blue);
		UMixAttackComponent::FindAttackComponent(Hero)->SetAttackType(MixGameplayTags::Attack_Ranged);

		// 设置Hero骨骼 设置Hero动画蓝图类
		FHeroModelInfo& ModelInfo = UMixAssetManager::Get().HeroModelInfo[MixGameplayTags::Creature_Name_Ashe];
		Hero->GetMesh()->SetSkeletalMesh(UMixAssetManager::Get().GetAssetSync(ModelInfo.Mesh));
		Hero->GetMesh()->SetAnimClass(ModelInfo.Anim);

		// 设置HeroSelf属性
		UMixHeroAttribute* HeroAttribute = NewObject<UMixHeroAttribute>();
		HeroAttribute->Init<FMixHeroAttributeData>(Hero, UMixAssetManager::Get().HeroAttributeData);

		// 生成HeroSelf Controller
		AMixHostHeroControllerFix* HeroController = GetWorld()->SpawnActor<AMixHostHeroControllerFix>(UMixAssetManager::Get().HostHeroController, SpawnTransform);
		if (!ensure(HeroController)) return;
		AMixGameMode* GameMode = Cast<AMixGameMode>(GetWorld()->GetAuthGameMode());
		if (!ensure(GameMode)) return;
		GameMode->SwapPlayerControllers(GetWorld()->GetFirstPlayerController(), HeroController);
		// GameMode->GenericPlayerInitialization(HostHeroController);
		Hero->SetIsHost(true);
		HeroController->Possess(Hero);
		HostHero = Hero;
	}

	// 生成Hero Lucian
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AActor::StaticClass(), "HeroSpawnPoint_Lucian", OutActors);
		if (!ensure(OutActors.IsValidIndex(0))) return;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FTransform SpawnTransform = OutActors[0]->GetActorTransform();
		AMixHero* Hero = GetWorld()->SpawnActor<AMixHero>(UMixAssetManager::Get().HeroModelInfo[MixGameplayTags::Creature_Name_Lucian].Class, SpawnTransform, SpawnParams);
		if (!ensure(Hero)) return;
		SpawnedHeros.AddUnique(Hero);
		Hero->SetCreatureName(MixGameplayTags::Creature_Name_Lucian);
		Hero->SetCreatureType(MixGameplayTags::Creature_Type_Hero);
		Hero->SetCreatureCamp(MixGameplayTags::Creature_Camp_Red);
		UMixAttackComponent::FindAttackComponent(Hero)->SetAttackType(MixGameplayTags::Attack_Ranged);

		// 设置Hero骨骼 设置Hero动画蓝图类
		FHeroModelInfo& ModelInfo = UMixAssetManager::Get().HeroModelInfo[MixGameplayTags::Creature_Name_Lucian];
		Hero->GetMesh()->SetSkeletalMesh(UMixAssetManager::Get().GetAssetSync(ModelInfo.Mesh));
		Hero->GetMesh()->SetAnimClass(ModelInfo.Anim);
		Hero->GetCapsuleComponent()->SetWorldScale3D(FVector(0.7f, 0.7f, 0.7f)); // TODO: 配表

		// 设置Hero属性
		UMixHeroAttribute* HeroAttribute = NewObject<UMixHeroAttribute>();
		HeroAttribute->Init<FMixHeroAttributeData>(Hero, UMixAssetManager::Get().HeroAttributeData);

		// 生成Hero Controller
		AMixHeroControllerFix* HeroController = GetWorld()->SpawnActor<AMixHeroControllerFix>(UMixAssetManager::Get().HeroModelInfo[MixGameplayTags::Creature_Name_Lucian].HeroController, SpawnTransform);
		if (!ensure(HeroController)) return;
		HeroController->Possess(Hero);
	}
}

void UMixLevelSubsystem::GenerateBatmans()
{
	TArray<AActor*> BlueSpawnPoints;
	TArray<AActor*> RedSpawnPoints;

	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AActor::StaticClass(), MixGlobalData::SpawnPoint_Batman_Blue, BlueSpawnPoints);
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AActor::StaticClass(), MixGlobalData::SpawnPoint_Batman_Red, RedSpawnPoints);

	for (const auto& SpawnPoint : BlueSpawnPoints)
	{
		SpawnBatman(SpawnPoint, MixGameplayTags::Creature_Camp_Blue);
	}
	for (const auto& SpawnPoint : RedSpawnPoints)
	{
		SpawnBatman(SpawnPoint, MixGameplayTags::Creature_Camp_Red);
	}
}

AMixBatman* UMixLevelSubsystem::SpawnBatman(const AActor* SpawnPoint, const FGameplayTag& Type)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FTransform SpawnTransform = SpawnPoint->GetActorTransform();
	AMixBatman* Batman = GetWorld()->SpawnActor<AMixBatman>(UMixAssetManager::Get().BatmanModelInfo[MixGameplayTags::Creature_Name_Batman].Class, SpawnTransform, SpawnParams);
	SpawnedBatmans.AddUnique(Batman);
	Batman->SetCreatureName(MixGameplayTags::Creature_Name_Batman);
	Batman->SetCreatureType(MixGameplayTags::Creature_Type_Batman);
	Batman->SetCreatureCamp(Type);
	UMixAttackComponent::FindAttackComponent(Batman)->SetAttackType(MixGameplayTags::Attack_Ranged);

	// 设置Batman属性
	UMixAttribute* Attribute = NewObject<UMixAttribute>();
	Attribute->Init<FMixAttributeData>(Batman, UMixAssetManager::Get().AttributeData);

	return Batman;
}
