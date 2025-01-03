// Fill out your copyright notice in the Description page of Project Settings.


#include "MixLevelSubsystem.h"

#include "MixAssetManager.h"
#include "MixGameSubsystem.h"
#include "Creature/Controller/Hero/MixHeroController.h"
#include "Creature/Creature/MixAttribute.h"
#include "Creature/Creature/MixHeroAttribute.h"
#include "Creature/Creature/Batman/MixBatman.h"
#include "Creature/Creature/Hero/MixHero.h"
#include "Creature/Creature/Hero/MixHeroInfo_Ashe.h"
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
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), UMixAssetManager::Get().HeroSpawnPointClass, "HeroSpawnPoint", OutActors);
	if (!ensure(OutActors.IsValidIndex(0))) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FTransform SpawnTransform = OutActors[0]->GetActorTransform();

	AMixHero* Hero = GetWorld()->SpawnActor<AMixHero>(UMixAssetManager::Get().HeroClass, SpawnTransform, SpawnParams);
	if (!ensure(Hero)) return;
	SpawnedHeros.AddUnique(Hero);

	TObjectPtr<AMixHeroInfo_Ashe> Ashe = GetWorld()->SpawnActor<AMixHeroInfo_Ashe>(AMixHeroInfo_Ashe::StaticClass());
	Ashe->Init();
	Ashe->SetHero(Hero);
	
	Hero->SetHeroInfo(Ashe);
	Hero->SetHeroName(MixGameplayTags::Hero_Name_Ashe);
	Hero->SetCreatureType(MixGameplayTags::Creature_Type_Hero_Self);

	// 读属性表
	// TODO: 整理成一种更友好的方式
	TSoftObjectPtr<UDataTable> AttributeDataSoftPtr = UMixAssetManager::Get().HeroAttributeData;
	const UDataTable* AttributeDT = UMixAssetManager::Get().GetDataTable(AttributeDataSoftPtr);
	if (!ensure(AttributeDT)) return;
	FMixHeroAttributeData* AttributeData = AttributeDT->FindRow<FMixHeroAttributeData>(TEXT("Ashe"), "AttributeData");
	
	UMixHeroAttribute* HeroAttribute = NewObject<UMixHeroAttribute>();
	HeroAttribute->Health = AttributeData->MaxHealth;
	HeroAttribute->MaxHealth = AttributeData->MaxHealth;
	HeroAttribute->Speed = AttributeData->Speed;
	HeroAttribute->AttackVal = AttributeData->AttackVal;
	HeroAttribute->Magic = AttributeData->MaxMagic;
	Hero->SetAttribute(HeroAttribute);
	Hero->GetHeadUI()->BP_OnAttributeAvaiable();

	AMixHeroController* HeroController = GetWorld()->SpawnActor<AMixHeroController>(UMixAssetManager::Get().HeroController, SpawnTransform);
	if (!ensure(HeroController)) return;

	AMixGameMode* GameMode = Cast<AMixGameMode>(GetWorld()->GetAuthGameMode());
	if (!ensure(GameMode)) return;

	GameMode->SwapPlayerControllers(GetWorld()->GetFirstPlayerController(), HeroController);
	// GameMode->GenericPlayerInitialization(HeroController);

	HeroController->Possess(Hero);
}

void UMixLevelSubsystem::GenerateBatman()
{
	// UClass* BpBatmanClass = LoadObject<UClass>(nullptr, BpBatmanClassPath);
	// if (!ensure(BpBatmanClass)) return;
	// UClass* BpSpawnPointClass = LoadObject<UClass>(nullptr, BpSpawnPointPath);
	// if (!ensure(BpSpawnPointClass)) return;

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), UMixAssetManager::Get().BatmanSpawnPointClass, "BatmanSpawnPoint", OutActors);
	if (!ensure(OutActors.IsValidIndex(0))) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FTransform SpawnTransform = OutActors[0]->GetActorTransform();
	AMixBatman* Batman = GetWorld()->SpawnActor<AMixBatman>(UMixAssetManager::Get().BatmanClass, SpawnTransform, SpawnParams);
	Batman->SetCreatureType(MixGameplayTags::Creature_Type_Batman_Enemy);

	// 读属性表
	TSoftObjectPtr<UDataTable> AttributeDataSoftPtr = UMixAssetManager::Get().AttributeData;
	const UDataTable* AttributeDT = UMixAssetManager::Get().GetDataTable(AttributeDataSoftPtr);
	if (!ensure(AttributeDT)) return;
	FMixAttributeData* AttributeData = AttributeDT->FindRow<FMixAttributeData>(TEXT("Batman"), "AttributeData");
	
	UMixAttribute* Attribute = NewObject<UMixAttribute>();
	Attribute->Health = AttributeData->MaxHealth;
	Attribute->MaxHealth = AttributeData->MaxHealth;
	Attribute->Speed = AttributeData->Speed;
	Attribute->AttackVal = AttributeData->AttackVal;
	Batman->SetAttribute(Attribute);
	Batman->GetHeadUI()->BP_OnAttributeAvaiable();
}
