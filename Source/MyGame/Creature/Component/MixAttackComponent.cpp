// Fill out your copyright notice in the Description page of Project Settings.


#include "MixAttackComponent.h"

#include "MixAssetManager.h"
#include "Utils/MixGameplayTags.h"
#include "Algo/MinElement.h"
#include "Creature/Ammo/MixTrackRangedAmmo.h"
#include "Creature/Controller/MixAIController.h"
#include "Creature/Controller/Hero/MixHostHeroControllerFix.h"
#include "Creature/Creature/MixAttribute.h"
#include "Creature/Creature/Hero/MixHero.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"

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
void UMixAttackComponent::SetAttackRangeHidden(bool bHidden) const
{
	AMixHero* HeroSelf = Cast<AMixHero>(Creature);
	if (!ensure(HeroSelf)) return;

	TArray<UActorComponent*> TaggedComponents = HeroSelf->GetComponentsByTag(UActorComponent::StaticClass(), MixGlobalData::AttackRangeComponent);
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

	TargetCreature = SelectTarget(Pos);
	if (TargetCreature)
	{
		TurnToTarget(TargetCreature);
	}
}

// Batman, Hero
void UMixAttackComponent::PrepareAttack(AMixCreature* Target)
{
	Creature->GetController()->StopMovement();
	bCanAIAttack = true;

	TargetCreature = Target;
	Cast<AMixAIController>(Creature->GetController())->SetFocus(TargetCreature);
}

// HeroSelf
AMixCreature* UMixAttackComponent::SelectTarget(const FVector& Pos)
{
	CreaturesInRange.Empty();

	AMixHero* HeroSelf = Cast<AMixHero>(Creature);
	FVector StartPos = HeroSelf->GetActorLocation();
	FVector EndPos = HeroSelf->GetActorLocation();

	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> OutHits;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1), UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel3)};
	UKismetSystemLibrary::CapsuleTraceMultiForObjects(GetWorld(), StartPos, EndPos, HeroSelf->GetAttribute()->AttackRange, MixGlobalData::CapsuleDetectionHalfHeight, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);

	for (const FHitResult& Hit : OutHits)
	{
		AActor* HitActor = Hit.GetActor();
		if (!ensure(HitActor)) continue;

		AMixCreature* HitCreature = Cast<AMixCreature>(HitActor);
		if (!ensure(HitCreature)) continue;

		// 排除自己；应该不需要，上面已经IgnoreSelf
		if (HitCreature->GetCreatureName() == Creature->GetCreatureName()) continue;

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

	if (!(ClosestCreature)) return nullptr;
	return *ClosestCreature;
}

void UMixAttackComponent::TurnToTarget(AMixCreature* Target)
{
	// SelfLocation = Creature->GetActorLocation();
	// SelfRotation = FRotator(0.0f, Creature->GetActorRotation().Yaw, 0.0f);
	// TargetLocation = Target->GetActorLocation();
	// SelfLookAtRotation = FRotator(0.0f, (TargetLocation - SelfLocation).Rotation().Yaw, 0.0f);
	//
	// TotalYawDifference = FMath::Fmod(SelfLookAtRotation.Yaw - SelfRotation.Yaw + 180.0f, 360.0f) - 180.0f;
	// YawPerFrame = TotalYawDifference / (KRotationTime / GetWorld()->GetDeltaSeconds());

	bIsHostRotating = true;
}

void UMixAttackComponent::TickTurnToTarget()
{
	if (Creature->IsIsHost())
	{
		if (bIsHostRotating)
		{
			// FRotator SelfNewRotation = FRotator(0.0f, Creature->GetActorRotation().Yaw + YawPerFrame, 0.0f);
			// Creature->SetActorRotation(SelfNewRotation);
			// float RotationBias = FMath::Abs(FMath::Fmod(SelfLookAtRotation.Yaw - SelfNewRotation.Yaw + 180.0f, 360.0f) - 180.0f);

			// float HostRotationYaw = Creature->GetActorRotation().Yaw;
			// float HostLookAtRotationYaw = (TargetCreature->GetActorLocation() - Creature->GetActorLocation()).Rotation().Yaw;
			// float TotalYawDiff = HostLookAtRotationYaw - HostRotationYaw;
			// float YawEachFrame = TotalYawDiff / (MixGlobalData::CreatureRotationTime / GetWorld()->GetDeltaSeconds());

			// Creature->SetActorRotation(FRotator(0.0f, Creature->GetActorRotation().Yaw + YawEachFrame, 0.0f));
			// float RotationBias = FMath::Abs(HostLookAtRotationYaw - Creature->GetActorRotation().Yaw);

			float YawPerFrame = MixGlobalData::RotateYawPerFrameBase / MixGlobalData::RotateDeltaTimeBase * GetWorld()->GetDeltaSeconds();
			float TargetYaw1 = TargetCreature->GetActorLocation().Rotation().Yaw;
			float TargetYaw2 = TargetCreature->GetActorRotation().Yaw;
			float CreatureYaw1 = Creature->GetActorLocation().Rotation().Yaw;
			float CreatureYaw2 = Creature->GetActorRotation().Yaw;
			float CreatureLookAtRotationYaw = (TargetCreature->GetActorLocation() - Creature->GetActorLocation()).Rotation().Yaw;
			float RotationDiff = CreatureLookAtRotationYaw - Creature->GetActorRotation().Yaw;
			if (RotationDiff > 180.0f)
			{
				RotationDiff -= 360.0f;
			}
			else if (RotationDiff < -180.0f)
			{
				RotationDiff += 360.0f;
			}
			YawPerFrame = RotationDiff > 0 ? YawPerFrame : -YawPerFrame;
			Creature->SetActorRotation(FRotator(0.0f, Creature->GetActorRotation().Yaw + YawPerFrame, 0.0f));

			if (FMath::Abs(RotationDiff) <= FMath::Abs(YawPerFrame) + MixGlobalData::RotationBias)
			{
				Creature->SetActorRotation(FRotator(0.0f, CreatureLookAtRotationYaw, 0.0f));
				bIsHostRotating = false;

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
	else
	{
		if (bCanAIAttack)
		{
			float CreatureRotationYaw = Creature->GetActorRotation().Yaw;
			float CreatureLookAtRotationYaw = (TargetCreature->GetActorLocation() - Creature->GetActorLocation()).Rotation().Yaw;
			float RotationDiff = FMath::Abs(CreatureLookAtRotationYaw - CreatureRotationYaw);

			if (RotationDiff <= MixGlobalData::RotationBias)
			{
				Creature->SetActorRotation(FRotator(0.0f, CreatureLookAtRotationYaw, 0.0f));
				Cast<AMixAIController>(Creature->GetController())->ClearFocus(EAIFocusPriority::Default);

				if (AttackType == MixGameplayTags::Attack_Ranged)
				{
					PerformRangedAttack();
				}
				else if (AttackType == MixGameplayTags::Attack_Melee)
				{
					PerformMeleeAttack();
				}

				bCanAIAttack = false;
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
		MontagePath = UMixAssetManager::Get().BatmanModelInfo[Creature->GetCreatureName()].AttackMontage;
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
	FTransform AmmoTransform;

	TSubclassOf<AActor> AmmoClass;
	if (Creature->GetCreatureType().MatchesTag(MixGameplayTags::Creature_Type_Hero))
	{
		AmmoClass = UMixAssetManager::Get().HeroModelInfo[Creature->GetCreatureName()].Ammo;
		AmmoTransform = Creature->GetMesh()->GetSocketTransform(MixGlobalData::LaunchPoint);
	}
	else if (Creature->GetCreatureType().MatchesTag(MixGameplayTags::Creature_Type_Batman))
	{
		AmmoClass = UMixAssetManager::Get().BatmanModelInfo[Creature->GetCreatureName()].Ammo;
		TArray<UActorComponent*> TaggedComponents = Creature->GetComponentsByTag(UActorComponent::StaticClass(), MixGlobalData::LaunchPoint);
		USceneComponent* AmmoPointComponent = Cast<USceneComponent>(TaggedComponents[0]);
		AmmoTransform = AmmoPointComponent->GetComponentToWorld();
	}

	FActorSpawnParameters AmmoParams;
	AmmoParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AmmoParams.CustomPreSpawnInitalization = [this](AActor* SpawnedActor)
	{
		AMixTrackRangedAmmo* Ammo = Cast<AMixTrackRangedAmmo>(SpawnedActor);
		if (!ensure(Ammo)) return;
		Ammo->SetAttacker(Creature);
		Ammo->SetTarget(TargetCreature); // 跟踪导弹，所以需要设Target
	};
	AMixTrackRangedAmmo* SpawnedActor = GetWorld()->SpawnActor<AMixTrackRangedAmmo>(AmmoClass, AmmoTransform, AmmoParams);
}