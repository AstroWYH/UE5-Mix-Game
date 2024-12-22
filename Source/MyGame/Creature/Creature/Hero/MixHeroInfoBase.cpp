// Fill out your copyright notice in the Description page of Project Settings.

#include "MixHeroInfoBase.h"

UMixHeroInfoBase::UMixHeroInfoBase() : Super()
{
}

TWeakObjectPtr<AMixHero> UMixHeroInfoBase::GetHero() const
{
	return Hero;
}

