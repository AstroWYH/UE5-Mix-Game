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

// HeroSelfִ��
void UMixAttackComponent::SetAttackRangeHidden(bool bHidden)
{
	AMixHero* HeroSelf = Cast<AMixHero>(Creature);
	if (!ensure(HeroSelf)) return;

	// ʾ��GetComponentsByTag���÷�����ʵһ����FindComponentByClass����
	TArray<UActorComponent*> TaggedComponents = HeroSelf->GetComponentsByTag(UActorComponent::StaticClass(), "AttackRangeComponent");
	for (UActorComponent* AttackRangeComponent : TaggedComponents)
	{
		if (!ensure(AttackRangeComponent)) continue;
		UStaticMeshComponent* AttackRangeMeshComponent = Cast<UStaticMeshComponent>(AttackRangeComponent);
		if (!ensure(AttackRangeMeshComponent)) continue;

		AttackRangeMeshComponent->SetHiddenInGame(bHidden);
	}
}

// ����HeroSelf
void UMixAttackComponent::PrepareAttack(const FVector& Pos)
{
	Creature->GetController()->StopMovement();

	AMixCreature* Target = SelectTarget(Pos);
	if (Target)
	{
		TurnToTarget(Target);
	}
}

// ��������
void UMixAttackComponent::PrepareAttack(AMixCreature* Target)
{
	Creature->GetController()->StopMovement();

	TurnToTarget(Target);
}

// �����HeroSelf
AMixCreature* UMixAttackComponent::SelectTarget(const FVector& Pos)
{
	// ��ȡ��Χ�ڵз�Creature
	CreaturesInRange.Empty();

	AMixHero* HeroSelf = Cast<AMixHero>(Creature);
	FVector StartPos = HeroSelf->GetActorLocation();
	FVector EndPos = HeroSelf->GetActorLocation();

	// DefaultEngine.ini�����˱༭����������Cfg��ECC_GameTraceChannel1��ӦEnemy��ObjType
	// TODO: ��ⷶΧ1000.0f���ã�AttackRangeĬ����500
	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> OutHits;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1)};
	UKismetSystemLibrary::CapsuleTraceMultiForObjects(GetWorld(), StartPos, EndPos, HeroSelf->GetAttribute()->AttackRange, 1000.0f, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);

	for (const FHitResult& Hit : OutHits)
	{
		AActor* HitActor = Hit.GetActor();
		if (!ensure(HitActor)) continue;

		// TODO: ������Ҫ��Ϊ�����Թ����ĵ�λ������ʲô��λ�������ģ���Ҫtag���ж�
		AMixCreature* HitCreature = Cast<AMixCreature>(HitActor);
		if (!ensure(HitCreature)) continue;

		CreaturesInRange.Add(HitCreature);
	}

	// ��Χ��û�ез�Creature�������й���
	if (CreaturesInRange.IsEmpty()) return nullptr;

	// ɸѡ��Χ�ڣ������λ������ĵз�Creature�����й���
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
	// ����Ŀ����ת
	SelfLocation = Creature->GetActorLocation();
	SelfRotation = FRotator(0.0f, Creature->GetActorRotation().Yaw, 0.0f);
	TargetLocation = Target->GetActorLocation();
	SelfLookAtRotation = FRotator(0.0f, (TargetLocation - SelfLocation).Rotation().Yaw, 0.0f);

	// ����ȷ�����ǶȽ�С�ķ�����ת
	TotalYawDifference = FMath::Fmod(SelfLookAtRotation.Yaw - SelfRotation.Yaw + 180.0f, 360.0f) - 180.0f;
	YawPerFrame = TotalYawDifference / (KRotationTime / GetWorld()->GetDeltaSeconds());

	// �ÿ�ʼת��״̬
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
			// ����ȡHost����Ӧ�õĳ������ڽ���
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
	// TODO: Ҫ����HeroȡMontage
	// Creature->BP_PerformAttack();
}

void UMixAttackComponent::PerformMeleeAttack()
{
	// TODO: �ܵ�������Χ��(move to)������̫��
}

void UMixAttackComponent::OnMontageNofify()
{
}
