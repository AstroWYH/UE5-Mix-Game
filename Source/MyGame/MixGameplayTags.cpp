// Fill out your copyright notice in the Description page of Project Settings.


#include "MixGameplayTags.h"

#include "Engine/EngineTypes.h"
#include "GameplayTagsManager.h"

namespace MixGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Hero_Name_Ashe, "Hero.Name.Ashe", "Hero.Name.Ashe");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Hero_Name_Zed, "Hero.Name.Zed", "Hero.Name.Zed");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Type_Q, "Ability.Type.Q", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Type_W, "Ability.Type.W", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Type_E, "Ability.Type.E", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Type_R, "Ability.Type.R", "");
}