// Fill out your copyright notice in the Description page of Project Settings.


#include "MixLevelSubsystem.h"

#include "MixAssetManager.h"
#include "MixGameSubsystem.h"
#include "Ability/MixAbilityMgr.h"
#include "Creature/Controller/Hero/MixHostHeroController.h"
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

void UMixLevelSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	if (!(InWorld.GetName() == "LOL")) return;

	GenerateHero();

	// 所有GameMgr都加上OnHeroSpawned接口
	TArray<UMixGameSubsystem*> GameSubsystems = InWorld.GetGameInstance()->GetSubsystemArray<UMixGameSubsystem>();
	for (UMixGameSubsystem* GameSubsystem : GameSubsystems)
	{
		if (!ensure(GameSubsystem)) continue;
		GameSubsystem->OnHeroSpawned();
	}
	
	GenerateBatman();
}

void UMixLevelSubsystem::GenerateHero()
{
	// 生成Ashe
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), UMixAssetManager::Get().HeroSpawnPointClass, "HeroSpawnPoint", OutActors);
	if (!ensure(OutActors.IsValidIndex(0))) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FTransform SpawnTransform = OutActors[0]->GetActorTransform();

	AMixHero* Hero = GetWorld()->SpawnActor<AMixHero>(UMixAssetManager::Get().BP_HeroClass_Ashe, SpawnTransform, SpawnParams);
	if (!ensure(Hero)) return;
	SpawnedHeros.AddUnique(Hero);

	Hero->SetHeroName(MixGameplayTags::Hero_Name_Ashe);
	Hero->SetCreatureType(MixGameplayTags::Creature_Type_Hero_Self);
	Hero->SetAttackType(MixGameplayTags::Attack_Ranged);
	Hero->GetMesh()->SetSkeletalMesh(UMixAssetManager::Get().GetAssetSync(UMixAssetManager::Get().Mesh_Ashe));
	Hero->GetMesh()->SetAnimClass(UMixAssetManager::Get().Anim_Ashe);
	
	// 读属性表 TODO: 整理成一种更友好的方式
	TSoftObjectPtr<UDataTable> AttributeDataSoftPtr = UMixAssetManager::Get().HeroAttributeData;
	const UDataTable* AttributeDT = UMixAssetManager::Get().GetAssetSync(AttributeDataSoftPtr);
	if (!ensure(AttributeDT)) return;
	FMixHeroAttributeData* AttributeData = AttributeDT->FindRow<FMixHeroAttributeData>(TEXT("Ashe"), "AttributeData");
	
	UMixHeroAttribute* HeroAttribute = NewObject<UMixHeroAttribute>();
	HeroAttribute->Health = AttributeData->MaxHealth;
	HeroAttribute->MaxHealth = AttributeData->MaxHealth;
	HeroAttribute->Speed = AttributeData->Speed;
	HeroAttribute->AttackVal = AttributeData->AttackVal;
	HeroAttribute->AttackRange = AttributeData->AttackRange;
	HeroAttribute->Magic = AttributeData->MaxMagic;
	Hero->SetAttribute(HeroAttribute);
	Hero->GetHeadUI()->BP_OnAttributeAvaiable();

	AMixHostHeroController* HeroController = GetWorld()->SpawnActor<AMixHostHeroController>(UMixAssetManager::Get().HostHeroController, SpawnTransform);
	if (!ensure(HeroController)) return;

	AMixGameMode* GameMode = Cast<AMixGameMode>(GetWorld()->GetAuthGameMode());
	if (!ensure(GameMode)) return;

	GameMode->SwapPlayerControllers(GetWorld()->GetFirstPlayerController(), HeroController);
	// GameMode->GenericPlayerInitialization(HostHeroController);

	HeroController->Possess(Hero);
}

void UMixLevelSubsystem::GenerateBatman()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), UMixAssetManager::Get().BatmanSpawnPointClass, "BatmanSpawnPoint", OutActors);
	if (!ensure(OutActors.IsValidIndex(0))) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FTransform SpawnTransform = OutActors[0]->GetActorTransform();
	AMixBatman* Batman = GetWorld()->SpawnActor<AMixBatman>(UMixAssetManager::Get().BatmanClass, SpawnTransform, SpawnParams);
	Batman->SetCreatureType(MixGameplayTags::Creature_Type_Batman_Enemy);
	Batman->SetAttackType(MixGameplayTags::Attack_Ranged);

	// 读属性表
	TSoftObjectPtr<UDataTable> AttributeDataSoftPtr = UMixAssetManager::Get().AttributeData;
	const UDataTable* AttributeDT = UMixAssetManager::Get().GetAssetSync(AttributeDataSoftPtr);
	if (!ensure(AttributeDT)) return;
	FMixAttributeData* AttributeData = AttributeDT->FindRow<FMixAttributeData>(TEXT("Batman"), "AttributeData");
	
	UMixAttribute* Attribute = NewObject<UMixAttribute>();
	Attribute->Health = AttributeData->MaxHealth;
	Attribute->MaxHealth = AttributeData->MaxHealth;
	Attribute->Speed = AttributeData->Speed;
	Attribute->AttackVal = AttributeData->AttackVal;
	Attribute->AttackRange = AttributeData->AttackRange;
	Batman->SetAttribute(Attribute);
	Batman->GetHeadUI()->BP_OnAttributeAvaiable();
}
