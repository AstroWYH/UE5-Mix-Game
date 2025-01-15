// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace MixGameplayTags
{
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Type_Hero);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Type_Hero_Self);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Type_Hero_Other);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Type_Hero_Friend);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Type_Hero_Enemy);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Type_Hero_Red);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Type_Hero_Blue);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Type_Batman);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Type_Batman_Friend);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Type_Batman_Enemy);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Type_Batman_Red);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Type_Batman_Blue);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Type_Tower);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Type_Tower_Friend);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Type_Tower_Enemy);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Type_Tower_Red);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Type_Tower_Blue);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Type_Monster);

	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Camp_Blue);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Camp_Red);

	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attack_Ranged);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attack_Melee);

	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Type_Q);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Type_W);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Type_E);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Type_R);

	// Hero
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Name_Ashe);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Name_Lucian);
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Name_Batman);
}

namespace MixGlobalData
{
	// BB
	const FName BB_bUnderAttack = TEXT("bUnderAttack");
	const FName BB_bHealthSafe = TEXT("bHealthSafe");
	const FName BB_TargetCreature = TEXT("TargetCreature");

	constexpr float BattleTime = 3.0f;
	constexpr float MoveDiff = 120.0f;
	constexpr float HealthSafePercent = 0.2f;

	const FName SpawnPoint_Batman_Blue = TEXT("SpawnPoint_Batman_Blue");
	const FName SpawnPoint_Batman_Red = TEXT("SpawnPoint_Batman_Red");

	constexpr float CapsuleDetectionHalfHeight = 1000.0f;
	constexpr float BatmanPerceptionRadius = 500.0f;
}