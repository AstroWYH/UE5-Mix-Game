// Fill out your copyright notice in the Description page of Project Settings.


#include "MixLevelSubsystem.h"

#include "Character/Batman/MixBatman.h"
#include "Kismet/GameplayStatics.h"

void UMixLevelSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	UClass* BpBatmanClass = LoadObject<UClass>(nullptr, BpBatmanClassPath);
	if (!ensure(BpBatmanClass)) return;
	
	UObject* MixOutter = GetOuter();
	UWorld* MixCastWorld = Cast<UWorld>(GetOuter());
	UWorld* MixWorld = GetWorld();
	
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), BpBatmanClass, "SpawnPoint", OutActors);
	if (!ensure(OutActors.IsValidIndex(0))) return;
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FTransform SpawnTransform = OutActors[0]->GetActorTransform();
	AMixBatman* Batman = GetWorld()->SpawnActor<AMixBatman>(BpBatmanClass, SpawnTransform, SpawnParams);
}