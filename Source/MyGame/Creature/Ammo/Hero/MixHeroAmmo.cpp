// Fill out your copyright notice in the Description page of Project Settings.


#include "MixHeroAmmo.h"
#include "GameFramework\FloatingPawnMovement.h"
#include "Creature/Creature/Batman/MixBatman.h"
#include "Components\BoxComponent.h"
#include "Creature/Ammo/MixAIAmmoController.h"
#include "Creature/Creature/MixCreature.h"
#include "Creature/Component/Health/MixCreatureHealthComponent.h"

// Sets default values
AMixHeroAmmo::AMixHeroAmmo()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

// Called when the game starts or when spawned
void AMixHeroAmmo::BeginPlay()
{
	Super::BeginPlay();

	UBoxComponent* ArrowBox = FindComponentByClass<UBoxComponent>();
	if (!ensure(ArrowBox)) return;

	ArrowBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMixHeroAmmo::HitTarget);

	// 2s后自毁
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, [this]()
	{
		Destroy();
	}, 2.0f, false);
}

void AMixHeroAmmo::BeginDestroy()
{
	Super::BeginDestroy();
}

// Called every frame
void AMixHeroAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMixHeroAmmo::HitTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                             const FHitResult& SweepResult)
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("OtherActor: %s"), *OtherActor->GetName()));

	AMixCreature* TargetCharacter = Cast<AMixCreature>(OtherActor);
	if (!ensure(TargetCharacter)) return;

	AttachToComponent(TargetCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "ArrowHit");
	AMixAIAmmoController* AmmoController = Cast<AMixAIAmmoController>(GetController());
	AmmoController->bCanLaunch = false;

	MakeDamage(AttackVal);
}