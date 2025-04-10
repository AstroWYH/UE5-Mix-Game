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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMixCreatureAttackComponent> CreatureAttackComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMixCreatureHealthComponent> CreatureHeathComponent;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMixWidgetComponent> WidgetComponentFix;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMixAttackComponent> AttackComponent;

public:
	TObjectPtr<class UMixAttackComponent> GetAttackComponent() const
	{
		return AttackComponent;
	}

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
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

protected:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FGameplayTag CreatureName;

public:
	FGameplayTag GetCreatureName() const
	{
		return CreatureName;
	}

	void SetCreatureName(const FGameplayTag& InHeroName)
	{
		CreatureName = InHeroName;
	}

protected:
	FGameplayTag CreatureCamp;

public:
	FGameplayTag GetCreatureCamp() const
	{
		return CreatureCamp;
	}

	void SetCreatureCamp(const FGameplayTag& InCamp)
	{
		CreatureCamp = InCamp;
	}

protected:
	uint32 Id;

private:
	uint32 GenerateId()
	{
		static uint32 GlobalId = 0;
		return ++GlobalId;
	}

public:
	uint32 GetId() const
	{
		return Id;
	}

protected:
	bool bIsHost = false;

public:
	bool IsIsHost() const
	{
		return bIsHost;
	}

	void SetIsHost(bool bInIsHost)
	{
		this->bIsHost = bInIsHost;
	}
};