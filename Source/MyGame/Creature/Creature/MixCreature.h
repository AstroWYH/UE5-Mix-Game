// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "UObject\UObjectGlobals.h"

#include "MixCreature.generated.h"

class UMixHeadUIWidget;
class UMixAttribute;
class UDataTable;

UCLASS(config=Game)
class MYGAME_API AMixCreature : public ACharacter
{
	GENERATED_BODY()

public:
	AMixCreature();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void PostRegisterAllComponents() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AMixCreature)
	TObjectPtr<class UMixCreatureAttackComponent> CreatureAttackComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AMixCreature)
	TObjectPtr<class UMixCreatureHealthComponent> CreatureHeathComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AMixCreature)
	TObjectPtr<class UMixWidgetComponent> WidgetComponentFix;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UMixHeadUIWidget> HeadUI;

public:
	TObjectPtr<UMixHeadUIWidget> GetHeadUI() const
	{
		return HeadUI;
	}

	void SetHeadUI(const TObjectPtr<UMixHeadUIWidget>& InHeadUI)
	{
		HeadUI = InHeadUI;
	}

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FGameplayTag CreatureType;

public:
	UFUNCTION(BlueprintCallable)
	void SetCreatureType(const FGameplayTag& Type)
	{
		CreatureType = Type;
	}

	UFUNCTION(BlueprintCallable)
	FGameplayTag GetCreatureType() const
	{
		return CreatureType;
	}

protected:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UMixAttribute* Attribute;

public:
	UMixAttribute* GetAttribute() const
	{
		return Attribute;
	}

	void SetAttribute(UMixAttribute* InAttribute)
	{
		Attribute = InAttribute;
	}
};