// Fill out your copyright notice in the Description page of Project Settings.


#include "MixGameplayTags.h"

#include "Engine/EngineTypes.h"
#include "GameplayTagsManager.h"

namespace MixGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Hero_Self, "Creature.Type.Hero.Self", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Hero_Friend, "Creature.Type.Hero.Friend", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Hero_Enemy, "Creature.Type.Hero.Enemy", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Batman_Friend, "Creature.Type.Batman.Friend", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Batman_Enemy, "Creature.Type.Batman.Enemy", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Tower, "Creature.Type.Tower", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Monster, "Creature.Type.Monster", "");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Hero_Name_Ashe, "Hero.Name.Ashe", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Hero_Name_Zed, "Hero.Name.Zed", "");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Type_Q, "Ability.Type.Q", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Type_W, "Ability.Type.W", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Type_E, "Ability.Type.E", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Type_R, "Ability.Type.R", "");
}