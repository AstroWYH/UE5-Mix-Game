#include "MixHeroInfo_Ashe.h"

#include "MixAssetManager.h"
#include "Creature/Controller/Hero/MixHeroController.h"
#include "Engine/AssetManager.h"

AMixHeroInfo_Ashe::AMixHeroInfo_Ashe() : Super()
{
}

void AMixHeroInfo_Ashe::Skill(EHeroOperateKey SkillKey)
{
	// 废弃，这里不需要准备这么早这些数据
	CurSkillKey = SkillKey;

	switch (SkillKey)
	{
	case EHeroOperateKey::Q:
		SkillMontagePath = &UMixAssetManager::Get().Skill_Ashe_Montage_Q;
		break;
	case EHeroOperateKey::W:
		SkillMontagePath = &UMixAssetManager::Get().Skill_Ashe_Montage_W;
		break;
	case EHeroOperateKey::E:
		SkillMontagePath = &UMixAssetManager::Get().Skill_Ashe_Montage_E;
		break;
	case EHeroOperateKey::R:
		SkillMontagePath = &UMixAssetManager::Get().Skill_Ashe_Montage_R;
		break;
	}

	// TODO: 这有一部分代码可以移动到父类
	StopMovement();
	TurnToMousePos();
}

void AMixHeroInfo_Ashe::SkillSpawn()
{
	if (CurSkillKey == EHeroOperateKey::Q)
	{
		// 发射飞剑
		FTransform SwordTrans = Hero->GetMesh()->GetSocketTransform("BowEmitterSocket");
		FActorSpawnParameters SwordParams;
		SwordParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* Sword = GetWorld()->SpawnActor<AActor>(UMixAssetManager::Get().Skill_Ashe_BP_Q, SwordTrans, SwordParams);

		// 生成陨石雨
		// 不能现取鼠标位置，应该用按键时候的鼠标位置
		// FVector MouseLocation = Cast<AMixHeroController>(Hero->GetController())->GetMouseClickFloorPosition();
		FTransform FallingStoneTrans(FQuat::Identity, AbilityMousePos, FVector(1.0f, 1.0f, 1.0f));
		FActorSpawnParameters FallingStoneParams;
		FallingStoneParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* FallingStone = GetWorld()->SpawnActor<AActor>(UMixAssetManager::Get().Skill_Ashe_BP_Q_Ext, FallingStoneTrans, FallingStoneParams);
	}
}
