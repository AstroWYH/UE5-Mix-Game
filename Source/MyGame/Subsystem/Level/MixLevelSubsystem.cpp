// Fill out your copyright notice in the Description page of Project Settings.


#include "MixLevelSubsystem.h"

#include "MixAssetManager.h"
#include "MixGameSubsystem.h"
#include "Creature/Controller/Hero/MixHeroController.h"
#include "Creature/Creature/Batman/MixBatman.h"
#include "Creature/Creature/Hero/MixHero.h"
#include "Creature/Creature/Hero/MixHeroInfo_Ashe.h"
#include "Game/MixGameInstance.h"
#include "Game/MixGameMode.h"
#include "Kismet/GameplayStatics.h"

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
}
