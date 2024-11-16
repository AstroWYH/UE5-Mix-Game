// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Character\MixCharacterAttackComponent.h"
#include "UObject\UObjectGlobals.h"

#include "MixCharacter.generated.h"

UCLASS(config=Game)
class MYGAME_API AMixCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMixCharacter();

public:
// 	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AMixCharacter, meta = (AllowPrivateAccess = "true"))
// 	TObjectPtr<class UMixCharacterAttackComponent> CharacterAttackComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AMixCharacter, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMixCharacterAttackComponent> CharacterAttackComponent2;
// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AMixCharacter, meta = (AllowPrivateAccess = "true"))
// 	TObjectPtr<UStaticMeshComponent> TestMesh3;

};