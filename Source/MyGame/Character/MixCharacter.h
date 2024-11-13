// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Character\MixCharacterHealthComponent.h"
#include "Character\MixCharacterAttackComponent.h"
#include "UObject\UObjectGlobals.h"

#include "MixCharacter.generated.h"

UCLASS(config=Game)
class MYGAME_API AMixCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMixCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};