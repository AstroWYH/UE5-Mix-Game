// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MixHeadUIWidget.generated.h"

class AMixCreature;
/**
 * 
 */
UCLASS()
class MYGAME_API UMixHeadUIWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	AMixCreature* Creature;

public:
	AMixCreature* GetOwner() const
	{
		return Creature;
	}

	void SetOwner(AMixCreature* InCreature)
	{
		Creature = InCreature;
	}

};