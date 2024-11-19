// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo/Batman/MixBatmanAmmo.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Character/Character/Host/MixHost.h"
#include "Ammo\MixAIAmmoController.h"

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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,
	                                 FString::Printf(TEXT("OtherActor: %s"), *OtherActor->GetName()));

	AMixHost* Host = Cast<AMixHost>(OtherActor);
	if (!ensure(Host)) return;

	AMixAIAmmoController* AmmoController = Cast<AMixAIAmmoController>(GetController());
	AmmoController->bCanLaunch = false;

	MakeDamage(AttackVal);

	UStaticMeshComponent* Sphere = FindComponentByClass<UStaticMeshComponent>();
	if (!ensure(Sphere)) return;
	Sphere->OnComponentBeginOverlap.RemoveAll(this);

	Destroy();
}