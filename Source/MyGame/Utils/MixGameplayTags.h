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
	MYGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Name_Tower);
}

namespace MixGlobalData
{
	// BB Hero & Batman
	const FName BB_TargetCreature = TEXT("TargetCreature");

	// BB Hero
	const FName BB_bUnderAttack = TEXT("bUnderAttack");
	const FName BB_bHealthSafe = TEXT("bHealthSafe");

	// BB Batman
	const FName BB_CurTargetIdx = TEXT("CurTargetIdx");
	const FName BB_bFriendHeroUnderAttack = TEXT("bFriendHeroUnderAttack");

	constexpr float UnderAttackTime = 3.0f;
	constexpr float MoveDiff = 10.0f;
	constexpr float PatrolDiff = 5.0f;
	constexpr float CheckPatrolDiff = 150.0f;
	constexpr float HealthSafePercent = 0.2f;

	const FName SpawnPoint_Batman_Blue = TEXT("SpawnPoint_Batman_Blue");
	const FName SpawnPoint_Batman_Red = TEXT("SpawnPoint_Batman_Red");
	const FName PathPoint_Batman = TEXT("PathPoint_Batman");
	
	const FName SpawnPoint_Tower_Blue = TEXT("SpawnPoint_Tower_Blue");
	const FName SpawnPoint_Tower_Red = TEXT("SpawnPoint_Tower_Red");

	const FName AttackRangeComponent = TEXT("AttackRangeComponent");

	constexpr float CapsuleDetectionHalfHeight = 1000.0f;
	constexpr float FriendCampPerceptionRadius = 800.0f;

	constexpr float RotationBias = 5.0f;
	constexpr float RotateYawPerFrameBase = 10.0f;
	constexpr float RotateDeltaTimeBase = 0.016f;

	constexpr float AmmoHiddenDistance = 20.0f;
	const FName LaunchPoint = TEXT("LaunchPoint");
}