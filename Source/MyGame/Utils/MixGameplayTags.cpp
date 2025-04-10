// Fill out your copyright notice in the Description page of Project Settings.


#include "MixGameplayTags.h"

#include "Engine/EngineTypes.h"
#include "GameplayTagsManager.h"

namespace MixGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Hero, "Creature.Type.Hero", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Hero_Self, "Creature.Type.Hero.Self", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Hero_Other, "Creature.Type.Hero.Other", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Hero_Friend, "Creature.Type.Hero.Friend", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Hero_Enemy, "Creature.Type.Hero.Enemy", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Hero_Red, "Creature.Type.Hero.Red", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Hero_Blue, "Creature.Type.Hero.Blue", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Batman, "Creature.Type.Batman", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Batman_Friend, "Creature.Type.Batman.Friend", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Batman_Enemy, "Creature.Type.Batman.Enemy", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Batman_Red, "Creature.Type.Batman.Red", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Batman_Blue, "Creature.Type.Batman.Blue", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Tower, "Creature.Type.Tower", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Tower_Friend, "Creature.Type.Tower.Friend", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Tower_Enemy, "Creature.Type.Tower.Enemy", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Tower_Red, "Creature.Type.Tower.Red", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Tower_Blue, "Creature.Type.Tower.Blue", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Type_Monster, "Creature.Type.Monster", "");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Camp_Blue, "Creature.Camp.Blue", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Camp_Red, "Creature.Camp.Red", "");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attack_Ranged, "Attack.Ranged", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attack_Melee, "Attack.Melee", "");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Type_Q, "Ability.Type.Q", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Type_W, "Ability.Type.W", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Type_E, "Ability.Type.E", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Type_R, "Ability.Type.R", "");

	// Hero
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Name_Ashe, "Creature.Name.Ashe", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Name_Lucian, "Creature.Name.Lucian", "");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Name_Batman, "Creature.Name.Batman", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Creature_Name_Tower, "Creature.Name.Tower", "");
}