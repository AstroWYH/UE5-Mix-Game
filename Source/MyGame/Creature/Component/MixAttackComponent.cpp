// Fill out your copyright notice in the Description page of Project Settings.


#include "MixAttackComponent.h"

#include "MixGameplayTags.h"
#include "Algo/MinElement.h"
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

// HeroSelf执行
void UMixAttackComponent::SetAttackRangeHidden(bool bHidden)
{
	AMixHero* HeroSelf = Cast<AMixHero>(Creature);
	if (!ensure(HeroSelf)) return;

	// 示范GetComponentsByTag的用法，其实一般用FindComponentByClass即可
	TArray<UActorComponent*> TaggedComponents = HeroSelf->GetComponentsByTag(UActorComponent::StaticClass(), "AttackRangeComponent");
	for (UActorComponent* AttackRangeComponent : TaggedComponents)
	{
		if (!ensure(AttackRangeComponent)) continue;
		UStaticMeshComponent* AttackRangeMeshComponent = Cast<UStaticMeshComponent>(AttackRangeComponent);
		if (!ensure(AttackRangeMeshComponent)) continue;

		AttackRangeMeshComponent->SetHiddenInGame(bHidden);
	}
}

// 对于HeroSelf
void UMixAttackComponent::PrepareAttack(const FVector& Pos)
{
	Creature->GetController()->StopMovement();

	AMixCreature* Target = SelectTarget(Pos);
	if (Target)
	{
		TurnToTarget(Target);
	}
}

// 对于其他
void UMixAttackComponent::PrepareAttack(AMixCreature* Target)
{
	Creature->GetController()->StopMovement();

	TurnToTarget(Target);
}

// 仅针对HeroSelf
AMixCreature* UMixAttackComponent::SelectTarget(const FVector& Pos)
{
	// 获取范围内敌方Creature
	CreaturesInRange.Empty();

	AMixHero* HeroSelf = Cast<AMixHero>(Creature);
	FVector StartPos = HeroSelf->GetActorLocation();
	FVector EndPos = HeroSelf->GetActorLocation();

	// DefaultEngine.ini配置了编辑器里新增的Cfg，ECC_GameTraceChannel1对应Enemy的ObjType
	// TODO: 检测范围1000.0f配置，AttackRange默认是500
	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> OutHits;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1)};
	UKismetSystemLibrary::CapsuleTraceMultiForObjects(GetWorld(), StartPos, EndPos, HeroSelf->GetAttribute()->AttackRange, 1000.0f, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);

	for (const FHitResult& Hit : OutHits)
	{
		AActor* HitActor = Hit.GetActor();
		if (!ensure(HitActor)) continue;

		// TODO: 后续需要改为，可以攻击的单位，不是什么单位都攻击的，需要tag来判断
		AMixCreature* HitCreature = Cast<AMixCreature>(HitActor);
		if (!ensure(HitCreature)) continue;

		CreaturesInRange.Add(HitCreature);
	}

	// 范围内没有敌方Creature，不进行攻击
	if (CreaturesInRange.IsEmpty()) return nullptr;

	// 筛选范围内，离鼠标位置最近的敌方Creature，进行攻击
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
	// 面向目标旋转
	SelfLocation = Creature->GetActorLocation();
	SelfRotation = FRotator(0.0f, Creature->GetActorRotation().Yaw, 0.0f);
	TargetLocation = Target->GetActorLocation();
	SelfLookAtRotation = FRotator(0.0f, (TargetLocation - SelfLocation).Rotation().Yaw, 0.0f);

	// 用于确保朝角度较小的方向旋转
	TotalYawDifference = FMath::Fmod(SelfLookAtRotation.Yaw - SelfRotation.Yaw + 180.0f, 360.0f) - 180.0f;
	YawPerFrame = TotalYawDifference / (KRotationTime / GetWorld()->GetDeltaSeconds());

	// 置开始转向状态
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
			// 最后获取Host最新应该的朝向，用于矫正
			FRotator FinalFixRotation = FRotator(0.0f, (TargetCreature->GetActorLocation() - Creature->GetActorLocation()).Rotation().Yaw, 0.0f);
			Creature->SetActorRotation(FinalFixRotation);
			bIsRotating = false;

			FGameplayTag AttackType = Creature->GetAttackType();
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
	// TODO: 要根据Hero取Montage
	// Creature->BP_PerformAttack();
}

void UMixAttackComponent::PerformMeleeAttack()
{
	// TODO: 跑到攻击范围内(move to)，播蒙太奇
}

void UMixAttackComponent::OnMontageNofify()
{
}
