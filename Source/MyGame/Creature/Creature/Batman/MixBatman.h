// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Creature/Creature/MixCreature.h"

#include "MixBatman.generated.h"

UCLASS(config=Game)
class MYGAME_API AMixBatman : public AMixCreature
{
	GENERATED_BODY()

public:
	AMixBatman();

	void BeginPlay() override;

};