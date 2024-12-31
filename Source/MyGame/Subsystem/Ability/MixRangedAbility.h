// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Creature/Ammo/MixNoTrackRangedAmmo.h"
#include "Subsystem/Ability/MixAbilityBase.h"
#include "MixRangedAbility.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API AMixRangedAbility : public AMixAbilityBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, META = (AllowPrivateAccess = true))
	TSubclassOf<AMixNoTrackRangedAmmo> AmmoClass;
};