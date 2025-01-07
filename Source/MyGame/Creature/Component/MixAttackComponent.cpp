// Fill out your copyright notice in the Description page of Project Settings.


#include "MixAttackComponent.h"

#include "MixAssetManager.h"
#include "MixGameplayTags.h"
#include "Algo/MinElement.h"
#include "Creature/Ammo/MixTrackRangedAmmo.h"
#include "Creature/Creature/MixAttribute.h"
#include "Creature/Creature/Hero/MixHero.h"
#include "Kismet/KismetSystemLibrary.h"

UMixAttackComponent::UMixAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMixAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	Creature = Cast<AMixCreature>(GetOwner());
}

void UMixAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TickTurnToTarget();
}

// HeroSelf
void UMixAttackComponent::SetAttackRangeHidden(bool bHidden)
{
	AMixHero* HeroSelf = Cast<AMixHero>(Creature);
	if (!ensure(HeroSelf)) return;

	TArray<UActorComponent*> TaggedComponents = HeroSelf->GetComponentsByTag(UActorComponent::StaticClass(), "AttackRangeComponent");
	for (UActorComponent* AttackRangeComponent : TaggedComponents)
	{
		if (!ensure(AttackRangeComponent)) continue;
		UStaticMeshComponent* AttackRangeMeshComponent = Cast<UStaticMeshComponent>(AttackRangeComponent);
		if (!ensure(AttackRangeMeshComponent)) continue;

		AttackRangeMeshComponent->SetHiddenInGame(bHidden);
	}
}

// HeroSelf
void UMixAttackComponent::PrepareAttack(const FVector& Pos)
{
	Creature->GetController()->StopMovement();

	AMixCreature* Target = SelectTarget(Pos);
	if (Target)
	{
		TurnToTarget(Target);
	}
}

void UMixAttackComponent::PrepareAttack(AMixCreature* Target)
{
	Creature->GetController()->StopMovement();

	TurnToTarget(Target);
}

// HeroSelf
AMixCreature* UMixAttackComponent::SelectTarget(const FVector& Pos)
{
	CreaturesInRange.Empty();

	AMixHero* HeroSelf = Cast<AMixHero>(Creature);
	FVector StartPos = HeroSelf->GetActorLocation();
	FVector EndPos = HeroSelf->GetActorLocation();

	// TODO: 1000.0f 该值不变
	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> OutHits;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1)};
	UKismetSystemLibrary::CapsuleTraceMultiForObjects(GetWorld(), StartPos, EndPos, HeroSelf->GetAttribute()->AttackRange, 1000.0f, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);

	for (const FHitResult& Hit : OutHits)
	{
		AActor* HitActor = Hit.GetActor();
		if (!ensure(HitActor)) continue;

		AMixCreature* HitCreature = Cast<AMixCreature>(HitActor);
		if (!ensure(HitCreature)) continue;

		CreaturesInRange.Add(HitCreature);
	}

	if (CreaturesInRange.IsEmpty()) return nullptr;

	return SelectClosestTarget(Pos);
}

AMixCreature* UMixAttackComponent::SelectClosestTarget(const FVector& Pos)
{
	AMixCreature** ClosestCreature = Algo::MinElementBy(CreaturesInRange, [Pos, this](const AMixCreature* Creature)
	{
		return FVector::Distance(Pos, Creature->GetActorLocation());
	});

	if (!ensure(ClosestCreature)) return nullptr;
	return *ClosestCreature;
}

void UMixAttackComponent::TurnToTarget(AMixCreature* Target)
{
	SelfLocation = Creature->GetActorLocation();
	SelfRotation = FRotator(0.0f, Creature->GetActorRotation().Yaw, 0.0f);
	TargetLocation = Target->GetActorLocation();
	SelfLookAtRotation = FRotator(0.0f, (TargetLocation - SelfLocation).Rotation().Yaw, 0.0f);

	TotalYawDifference = FMath::Fmod(SelfLookAtRotation.Yaw - SelfRotation.Yaw + 180.0f, 360.0f) - 180.0f;
	YawPerFrame = TotalYawDifference / (KRotationTime / GetWorld()->GetDeltaSeconds());

	bIsRotating = true;

	TargetCreature = Target;
}

void UMixAttackComponent::TickTurnToTarget()
{
	if (bIsRotating)
	{
		FRotator SelfNewRotation = FRotator(0.0f, Creature->GetActorRotation().Yaw + YawPerFrame, 0.0f);
		Creature->SetActorRotation(SelfNewRotation);

		float RotationDiff = FMath::Abs(FMath::Fmod(SelfLookAtRotation.Yaw - SelfNewRotation.Yaw + 180.0f, 360.0f) - 180.0f);
		if (RotationDiff <= 6.0f)
		{
			FRotator FinalFixRotation = FRotator(0.0f, (TargetCreature->GetActorLocation() - Creature->GetActorLocation()).Rotation().Yaw, 0.0f);
			Creature->SetActorRotation(FinalFixRotation);
			bIsRotating = false;

			if (AttackType == MixGameplayTags::Attack_Ranged)
			{
				PerformRangedAttack();
			}
			else if (AttackType == MixGameplayTags::Attack_Melee)
			{
				PerformMeleeAttack();
			}
		}
	}
}

void UMixAttackComponent::PerformRangedAttack()
{
	FSoftObjectPath MontagePath;
	if (Creature->GetCreatureType().MatchesTag(MixGameplayTags::Creature_Type_Hero))
	{
		MontagePath = UMixAssetManager::Get().HeroModelInfo[Creature->GetCreatureName()].AttackMontage;
	}
	else if (Creature->GetCreatureType().MatchesTag(MixGameplayTags::Creature_Type_Batman))
	{
		MontagePath = UMixAssetManager::Get().CreatureModelInfo[Creature->GetCreatureName()].AttackMontage;
	}

	FStreamableDelegate OnMontageLoaded = FStreamableDelegate::CreateLambda([MontagePath, this]()
	{
		UObject* LoadedAsset = MontagePath.ResolveObject();
		if (LoadedAsset)
		{
			UAnimMontage* RangedAttackMontage = Cast<UAnimMontage>(LoadedAsset);
			if (RangedAttackMontage)
			{
				Creature->PlayAnimMontage(RangedAttackMontage);
			}
		}
	});
	UMixAssetManager::Get().GetAssetASync(MontagePath, OnMontageLoaded);
}

void UMixAttackComponent::PerformMeleeAttack()
{
	// TODO: 
}

void UMixAttackComponent::OnRangedMontageNofify()
{
	FName LaunchPoint("LaunchPoint");
	FTransform AmmoTransform;

	TSubclassOf<AActor> AmmoClass;
	if (Creature->GetCreatureType().MatchesTag(MixGameplayTags::Creature_Type_Hero))
	{
		 AmmoClass = UMixAssetManager::Get().HeroModelInfo[Creature->GetCreatureName()].Ammo;
		 AmmoTransform = Creature->GetMesh()->GetSocketTransform(LaunchPoint);
	}
	else if (Creature->GetCreatureType().MatchesTag(MixGameplayTags::Creature_Type_Batman))
	{
		AmmoClass = UMixAssetManager::Get().CreatureModelInfo[Creature->GetCreatureName()].Ammo;
		TArray<UActorComponent*> TaggedComponents = Creature->GetComponentsByTag(UActorComponent::StaticClass(), LaunchPoint);
		USceneComponent* AmmoPointComponent = Cast<USceneComponent>(TaggedComponents[0]);
		AmmoTransform = AmmoPointComponent->GetComponentToWorld();
	}

	FActorSpawnParameters AmmoParams;
	AmmoParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AmmoParams.CustomPreSpawnInitalization = [this](AActor* SpawnedActor)
		{
			AMixTrackRangedAmmo* Ammo = Cast<AMixTrackRangedAmmo>(SpawnedActor);
			if (!ensure(Ammo)) return;
			Ammo->SetShooter(Creature);
			Ammo->SetTarget(TargetCreature); // 跟踪导弹，所以需要设Target
		};
	AMixTrackRangedAmmo* SpawnedActor = GetWorld()->SpawnActor<AMixTrackRangedAmmo>(AmmoClass, AmmoTransform, AmmoParams);

}
