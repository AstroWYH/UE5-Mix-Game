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
	// UE远古bug，重命名CharacterAttackComponent为CharacterAttackComponent2
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AMixCharacter, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMixCharacterAttackComponent> CharacterAttackComponent2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AMixCharacter, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMixCharacterHealthComponent> CharacterHeathComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AMixCharacter, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> HeadComponent;
};