// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UObject\UObjectGlobals.h"

#include "MixCreature.generated.h"

UCLASS(config=Game)
class MYGAME_API AMixCreature : public ACharacter
{
	GENERATED_BODY()

public:
	AMixCreature();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AMixCreature)
	TObjectPtr<class UMixCreatureAttackComponent> CreatureAttackComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AMixCreature)
	TObjectPtr<class UMixCreatureHealthComponent> CreatureHeathComponentSup;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AMixCreature)
	TObjectPtr<class UWidgetComponent> HeadComponent;
};