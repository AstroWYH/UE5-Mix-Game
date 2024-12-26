#pragma once

#include "MixHeroInfoBase.h"
#include "MixHeroInfo_Ashe.generated.h"

struct FStreamableHandle;

UCLASS()
class AMixHeroInfo_Ashe :public AMixHeroInfoBase
{
	GENERATED_BODY()

public:
	AMixHeroInfo_Ashe();

public:
	virtual void Skill(EHeroOperateKey SkillKey) override;

public:
	virtual void SkillSpawn() override;

};
