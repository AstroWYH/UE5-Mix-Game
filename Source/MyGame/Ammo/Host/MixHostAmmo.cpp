// Fill out your copyright notice in the Description page of Project Settings.


#include "MixHostAmmo.h"
#include "GameFramework\FloatingPawnMovement.h"
#include "Character\Batman\MixBatman.h"
#include "Components\BoxComponent.h"
#include "Ammo\MixAIAmmoController.h"

// Sets default values
AMixHostAmmo::AMixHostAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

// Called when the game starts or when spawned
void AMixHostAmmo::BeginPlay()
{
	Super::BeginPlay();

	UBoxComponent* ArrowBox = FindComponentByClass<UBoxComponent>();
	if (!ensure(ArrowBox)) return;

	ArrowBox->OnComponentBeginOverlap.AddDynamic(this, &AMixHostAmmo::HitTarget);

	// 2s后自毁
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, [this]()
		{
			Destroy();
		}, 2.0f, false);
}

// Called every frame
void AMixHostAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMixHostAmmo::HitTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
// 	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("OtherActor: %s"), *OtherActor->GetName()));

	AMixBatman* Batman = Cast<AMixBatman>(OtherActor);
	if (!ensure(Batman)) return;

	AttachToComponent(Batman->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "ArrowHit");
	AMixAIAmmoController* AmmoController = Cast<AMixAIAmmoController>(GetController());
	AmmoController->bCanLaunch = false;
}
