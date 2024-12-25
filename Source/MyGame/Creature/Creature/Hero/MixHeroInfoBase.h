// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MixHero.h"

#include "MixHeroInfoBase.generated.h"

struct FStreamableHandle;
class AMixHero;

UCLASS()
class UMixHeroInfoBase : public UObject
{
	GENERATED_BODY()

public:
	UMixHeroInfoBase();

public:
	virtual void Skill_Q() {};
	virtual void Skill_W() {};
	virtual void Skill_E() {};
	virtual void Skill_R() {};

protected:
	TWeakObjectPtr<AMixHero> Hero;

protected:
	TSharedPtr<FStreamableHandle> SkillMontageHandle_Q;
	TSharedPtr<FStreamableHandle> SkillMontageHandle_W;
	TSharedPtr<FStreamableHandle> SkillMontageHandle_E;
	TSharedPtr<FStreamableHandle> SkillMontageHandle_R;

public:
	void SetHero(AMixHero* InHero);

	TWeakObjectPtr<AMixHero> GetHero() const;
};
