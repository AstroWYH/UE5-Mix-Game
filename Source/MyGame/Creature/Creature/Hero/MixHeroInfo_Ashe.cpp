#include "MixHeroInfo_Ashe.h"

#include "MixAssetManager.h"
#include "Engine/AssetManager.h"

UMixHeroInfo_Ashe::UMixHeroInfo_Ashe() : Super()
{
}

void UMixHeroInfo_Ashe::Skill_Q()
{
	UE_LOG(LogTemp, Display, TEXT("艾希释放了Q技能"));

	auto Skill = [this]()
	{
			UAnimMontage* Skill_Ashe_Q = Cast<UAnimMontage>(UMixAssetManager::Get().Skill_Ashe_Q.ResolveObject());
			if (!ensure(Skill_Ashe_Q)) return;

			Hero->PlayAnimMontage(Skill_Ashe_Q);
	};

	if (SkillMontageHandle_Q.IsValid())
	{
		Skill();
	}
	else
	{
		SkillMontageHandle_Q = UAssetManager::GetStreamableManager().RequestAsyncLoad(UMixAssetManager::Get().Skill_Ashe_Q, FStreamableDelegate::CreateLambda(Skill));
	}
}

void UMixHeroInfo_Ashe::Skill_W()
{
	UE_LOG(LogTemp, Display, TEXT("艾希释放了W技能"));
}

void UMixHeroInfo_Ashe::Skill_E()
{
	UE_LOG(LogTemp, Display, TEXT("艾希释放了E技能"));
}

void UMixHeroInfo_Ashe::Skill_R()
{
	UE_LOG(LogTemp, Display, TEXT("艾希释放了R技能"));
}
