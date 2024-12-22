// Fill out your copyright notice in the Description page of Project Settings.


#include "MixLevelSubsystem.h"

#include "Creature/Creature/Batman/MixBatman.h"
#include "Kismet/GameplayStatics.h"

void UMixLevelSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UMixLevelSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	// GenerateHero();
	GenerateBatman();
}

void UMixLevelSubsystem::GenerateHero()
{
	// TODO: 暂时写一套一样的代码，后续配表
	UClass* BpBatmanClass = LoadObject<UClass>(nullptr, BpBatmanClassPath);
	if (!ensure(BpBatmanClass)) return;

	UClass* BpSpawnPointClass = LoadObject<UClass>(nullptr, BpSpawnPointPath);
	if (!ensure(BpSpawnPointClass)) return;

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), BpSpawnPointClass, "SpawnPoint", OutActors);
	if (!ensure(OutActors.IsValidIndex(0))) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FTransform SpawnTransform = OutActors[0]->GetActorTransform();
	AMixBatman* Batman = GetWorld()->SpawnActor<AMixBatman>(BpBatmanClass, SpawnTransform, SpawnParams);
}

void UMixLevelSubsystem::GenerateBatman()
{
	UClass* BpBatmanClass = LoadObject<UClass>(nullptr, BpBatmanClassPath);
	if (!ensure(BpBatmanClass)) return;

	UClass* BpSpawnPointClass = LoadObject<UClass>(nullptr, BpSpawnPointPath);
	if (!ensure(BpSpawnPointClass)) return;

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), BpSpawnPointClass, "SpawnPoint", OutActors);
	if (!ensure(OutActors.IsValidIndex(0))) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FTransform SpawnTransform = OutActors[0]->GetActorTransform();
	AMixBatman* Batman = GetWorld()->SpawnActor<AMixBatman>(BpBatmanClass, SpawnTransform, SpawnParams);
}
