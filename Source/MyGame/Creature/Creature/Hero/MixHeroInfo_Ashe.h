#pragma once

#include "MixHeroInfoBase.h"
#include "MixHeroInfo_Ashe.generated.h"

UCLASS()
class UMixHeroInfo_Ashe :public UMixHeroInfoBase
{
	GENERATED_BODY()

public:
	UMixHeroInfo_Ashe();

public:
	virtual void Skill_Q() override;
	virtual void Skill_W() override;
	virtual void Skill_E() override;
	virtual void Skill_R() override;
};
