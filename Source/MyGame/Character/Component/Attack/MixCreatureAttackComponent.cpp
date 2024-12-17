#include "MixCreatureAttackComponent.h"
#include "Character/Character/MixCreature.h"
#include "Engine\AssetManager.h"

void UMixCreatureAttackComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UMixCreatureAttackComponent::PreAttack()
{
	StopMovement();
	bool bSelect = SelectTarget();
	if (bSelect) TurnToTarget();
}

void UMixCreatureAttackComponent::StopMovement()
{
}

bool UMixCreatureAttackComponent::SelectTarget()
{
	return true;
}

void UMixCreatureAttackComponent::TurnToTarget()
{
	// 面向目标旋转
	SelfLocation = Creature->GetActorLocation();
	SelfRotation = FRotator(0.0f, Creature->GetActorRotation().Yaw, 0.0f);
	TargetLocation = SelectCharacterTarget->GetActorLocation();
	SelfLookAtRotation = FRotator(0.0f, (TargetLocation - SelfLocation).Rotation().Yaw, 0.0f);

	// 用于确保朝角度较小的方向旋转
	TotalYawDifference = FMath::Fmod(SelfLookAtRotation.Yaw - SelfRotation.Yaw + 180.0f, 360.0f) - 180.0f;
	YawPerFrame = TotalYawDifference / (KRotationTime / GetWorld()->GetDeltaSeconds());

	// 置开始转向状态
	bIsRotating = true;
}

void UMixCreatureAttackComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                                 FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TickRotateToTarget();
}

void UMixCreatureAttackComponent::TickRotateToTarget()
{
	if (bIsRotating)
	{
		FRotator SelfNewRotation = FRotator(0.0f, Creature->GetActorRotation().Yaw + YawPerFrame, 0.0f);
		Creature->SetActorRotation(SelfNewRotation);

		float RotationDiff = FMath::Abs(
			FMath::Fmod(SelfLookAtRotation.Yaw - SelfNewRotation.Yaw + 180.0f, 360.0f) - 180.0f);
		if (RotationDiff <= 6.0f)
		{
			// 最后获取Host最新应该的朝向，用于矫正
			FRotator FinalFixRotation = FRotator(
				0.0f, (SelectCharacterTarget->GetActorLocation() - Creature->GetActorLocation()).Rotation().Yaw,
				0.0f);
			Creature->SetActorRotation(FinalFixRotation);
			bIsRotating = false;

			// 矫正朝向后播Montage
			PlayAttackMontage();
		}
	}
}

void UMixCreatureAttackComponent::PlayAttackMontage()
{
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	StreamableManager.RequestAsyncLoad(AttackMontagePath, FStreamableDelegate::CreateLambda([this]()
	{
		UAnimMontage* AttackAnimMontage = Cast<UAnimMontage>(AttackMontagePath.TryLoad());
		if (!ensure(AttackAnimMontage)) return;

		Creature->PlayAnimMontage(AttackAnimMontage);
		// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("play attack montage")));
	}));
}

void UMixCreatureAttackComponent::AttackSpawn()
{
}