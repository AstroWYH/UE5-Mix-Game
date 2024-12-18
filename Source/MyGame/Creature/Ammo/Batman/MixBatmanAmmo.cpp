// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature/Ammo/Batman/MixBatmanAmmo.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Creature/Creature/Hero/MixHero.h"
#include "Creature/Ammo/MixAIAmmoController.h"

void AMixBatmanAmmo::BeginPlay()
{
	Super::BeginPlay();

	UStaticMeshComponent* Sphere = FindComponentByClass<UStaticMeshComponent>();
	if (!ensure(Sphere)) return;

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMixBatmanAmmo::HitTarget);
}

void AMixBatmanAmmo::BeginDestroy()
{
	Super::BeginDestroy();
}

void AMixBatmanAmmo::HitTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                               const FHitResult& SweepResult)
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("OtherActor: %s"), *OtherActor->GetName()));

	AMixHero* Host = Cast<AMixHero>(OtherActor);
	if (!ensure(Host)) return;

	AMixAIAmmoController* AmmoController = Cast<AMixAIAmmoController>(GetController());
	AmmoController->bCanLaunch = false;

	MakeDamage(AttackVal);
	Destroy();
}