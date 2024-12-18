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

	virtual void BeginPlay() override;

	virtual void PostRegisterAllComponents() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AMixCreature)
	TObjectPtr<class UMixCreatureAttackComponent> CreatureAttackComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AMixCreature)
	TObjectPtr<class UMixCreatureHealthComponent> CreatureHeathComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AMixCreature)
	TObjectPtr<class UWidgetComponent> HeadComponent;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AMixCreature)
	TSubclassOf<UUserWidget> HeadUIClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> HeadUI;
};