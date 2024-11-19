// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Character/Component/Attack/MixCharacterAttackComponent.h"
#include "UObject\UObjectGlobals.h"

#include "MixCharacter.generated.h"

UCLASS(config=Game)
class MYGAME_API AMixCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMixCharacter();

public:
	// UEÔ¶¹Åbug£¬ÖØÃüÃûCharacterAttackComponentÎªCharacterAttackComponent2
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AMixCharacter, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMixCharacterAttackComponent> CharacterAttackComponent2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AMixCharacter, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMixCharacterHealthComponent> CharacterHeathComponent;
};