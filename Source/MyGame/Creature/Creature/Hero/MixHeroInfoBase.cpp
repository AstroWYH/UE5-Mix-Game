// Fill out your copyright notice in the Description page of Project Settings.

#include "MixHeroInfoBase.h"

#include "Creature/Controller/Hero/MixHeroController.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

AMixHeroInfoBase::AMixHeroInfoBase() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMixHeroInfoBase::Init()
{
	SkillMontageHandles.Add(EHeroOperateKey::Q, nullptr);
	SkillMontageHandles.Add(EHeroOperateKey::W, nullptr);
	SkillMontageHandles.Add(EHeroOperateKey::E, nullptr);
	SkillMontageHandles.Add(EHeroOperateKey::R, nullptr);
}

void AMixHeroInfoBase::StopMovement()
{
	// 停止角色位移
	AMixHeroController* HeroController = Cast<AMixHeroController>(Hero->GetController());
	if (!ensure(HeroController)) return;

	HeroController->StopMovement();
}

void AMixHeroInfoBase::TurnToMousePos()
{
	AMixHeroController* HeroController = Cast<AMixHeroController>(Hero->GetController());
	if (!ensure(HeroController)) return;

	// 面向目标旋转
	SelfLocation = Hero->GetActorLocation();
	SelfRotation = FRotator(0.0f, Hero->GetActorRotation().Yaw, 0.0f);
	TargetLocation = HeroController->GetMouseClickFloorPosition();
	SelfLookAtRotation = FRotator(0.0f, (TargetLocation - SelfLocation).Rotation().Yaw, 0.0f);

	// 用于确保朝角度较小的方向旋转
	TotalYawDifference = FMath::Fmod(SelfLookAtRotation.Yaw - SelfRotation.Yaw + 180.0f, 360.0f) - 180.0f;
	YawPerFrame = TotalYawDifference / (KRotationTime / GetWorld()->GetDeltaSeconds());

	// 置开始转向状态
	bIsRotating = true;
}

void AMixHeroInfoBase::TickTurnToMousePos()
{
	if (bIsRotating)
	{
		FRotator SelfNewRotation = FRotator(0.0f, Hero->GetActorRotation().Yaw + YawPerFrame, 0.0f);
		Hero->SetActorRotation(SelfNewRotation);

		float RotationDiff = FMath::Abs(
			FMath::Fmod(SelfLookAtRotation.Yaw - SelfNewRotation.Yaw + 180.0f, 360.0f) - 180.0f);
		if (RotationDiff <= 6.0f)
		{
			// 最后获取Hero最新应该的朝向，用于矫正
			FRotator FinalFixRotation = FRotator(
				0.0f, (TargetLocation - Hero->GetActorLocation()).Rotation().Yaw,
				0.0f);
			Hero->SetActorRotation(FinalFixRotation);
			bIsRotating = false;

			// 记录技能施法的鼠标位置
			AMixHeroController* HeroController = Cast<AMixHeroController>(Hero->GetController());
			if (!ensure(HeroController)) return;

			// 矫正朝向后播Montage
			PlaySkillMontage();
		}
	}
}

void AMixHeroInfoBase::PlaySkillMontage()
{
	auto PlaySkillMontageFunc = [this]()
		{
			UAnimMontage* SkillMontage = Cast<UAnimMontage>(SkillMontagePath->ResolveObject());
			if (!ensure(SkillMontage)) return;

			Hero->PlayAnimMontage(SkillMontage);
		};

	if (!ensure(SkillMontageHandles.Contains(CurSkillKey))) return;

	if (SkillMontageHandles[CurSkillKey].IsValid())
	{
		PlaySkillMontageFunc();
	}
	else
	{
		SkillMontageHandles[CurSkillKey] = UAssetManager::GetStreamableManager().RequestAsyncLoad(*SkillMontagePath, FStreamableDelegate::CreateLambda(PlaySkillMontageFunc));
	}
}

void AMixHeroInfoBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TickTurnToMousePos();
}

void AMixHeroInfoBase::SetHero(AMixHero* InHero)
{
	Hero = InHero;
}

TWeakObjectPtr<AMixHero> AMixHeroInfoBase::GetHero() const
{
	return Hero;
}

void AMixHeroInfoBase::SetIsRotating(bool bInIsRotating)
{
	bIsRotating = bInIsRotating;
}

inline void AMixHeroInfoBase::SetSkillCastMousePos(FVector InSkillCastMousePos)
{
	AbilityMousePos = InSkillCastMousePos;
}

