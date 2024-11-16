#include "MixCharacterAttackComponent.h"
#include "Character\MixCharacter.h"

void UMixCharacterAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	MixCharacter = Cast<AMixCharacter>(GetOwner());
	if (!ensure(MixCharacter.IsValid())) return;
}

void UMixCharacterAttackComponent::PreAttack()
{
	StopMovement();
	SelectTarget();
	TurnToTarget();
}

void UMixCharacterAttackComponent::StopMovement()
{

}

void UMixCharacterAttackComponent::SelectTarget()
{

}

void UMixCharacterAttackComponent::TurnToTarget()
{
	// 面向目标旋转
	SelfLocation = MixCharacter->GetActorLocation();
	SelfRotation = FRotator(0.0f, MixCharacter->GetActorRotation().Yaw, 0.0f);
	TargetLocation = SelectCharacterTarget->GetActorLocation();
	SelfLookAtRotation = FRotator(0.0f, (TargetLocation - SelfLocation).Rotation().Yaw, 0.0f);

	// 用于确保朝角度较小的方向旋转
	TotalYawDifference = FMath::Fmod(SelfLookAtRotation.Yaw - SelfRotation.Yaw + 180.0f, 360.0f) - 180.0f;
	YawPerFrame = TotalYawDifference / (KRotationTime / GetWorld()->GetDeltaSeconds());

	// 置开始转向状态
	bIsRotating = true;
}
