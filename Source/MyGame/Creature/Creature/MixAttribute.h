// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MixAssetManager.h"
#include "MixCreature.h"
#include "Utils/MixGameplayTags.h"
#include "Data/Attribute/MixHeroAttributeData.h"
#include "Utils/UMixTagHelper.h"
#include "UI/HeadUI/MixHeadUIWidget.h"
#include "UObject/Object.h"
#include "MixAttribute.generated.h"

class AMixCreature;
class UDataTable;
struct FMixAttributeData;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API UMixAttribute : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Speed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 AttackVal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 DefenseVal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 AttackRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 AttackSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 HeadUILen;

public:
	template <typename DataClass>
	void Init(AMixCreature* Creature, const TSoftObjectPtr<UDataTable>& DataTablePtr)
	{
		const UDataTable* AttributeDT = UMixAssetManager::Get().GetAssetSync(DataTablePtr);
		if (!ensure(AttributeDT)) return;

		FString CreatureName = UUMixTagHelper::GetLastNameFromGameplayTag(Creature->GetCreatureName());
		DataClass* AttributeData = AttributeDT->FindRow<DataClass>(FName(*CreatureName), "AttributeData");
		InitAttributes(Creature, AttributeDT, AttributeData);

		OwnerCreature = Creature;
		Creature->SetAttribute(this);
		Creature->GetHeadUI()->BP_AttributeAvaiable();
	}

	template <typename DataClass>
	void InitAttributes(AMixCreature* Creature, const UDataTable* AttributeDT, const DataClass* AttributeData)
	{
		Health = AttributeData->MaxHealth;
		MaxHealth = AttributeData->MaxHealth;
		Speed = AttributeData->Speed;
		AttackVal = AttributeData->AttackVal;
		AttackRange = AttributeData->AttackRange;
		AttackSpeed = AttributeData->AttackSpeed;
		HeadUILen = AttributeData->HeadUILen;

		if (TIsSame<DataClass, FMixHeroAttributeData>::Value)
		{
			InitChildAttributes(Creature, AttributeDT, static_cast<const FMixHeroAttributeData*>(AttributeData));
		}
	}
	
	virtual void InitChildAttributes(AMixCreature* Creature, const UDataTable* AttributeDT, const FMixHeroAttributeData* AttributeData) {}

public:
	virtual void ApplyHealth(AMixCreature* Attacker, int32 Val);

	void Death() const;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMixOnDeath);
	UPROPERTY(BlueprintAssignable)
	FMixOnDeath OnDeath;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMixOnApplyHealth, int32, ApplyVal, int32, Health, int32, MaxHealth);
	UPROPERTY(BlueprintAssignable)
	FMixOnApplyHealth OnApplyHealth;
	
protected:
	AMixCreature* OwnerCreature;
	
};