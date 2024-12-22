#include "MixHeroInfo_Ashe.h"

UMixHeroInfo_Ashe::UMixHeroInfo_Ashe() : Super()
{
}

void UMixHeroInfo_Ashe::Skill_Q()
{
	UE_LOG(LogTemp, Display, TEXT("艾希释放了Q技能"));

	// Hero->PlayMontage(AshePath); // ...
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
