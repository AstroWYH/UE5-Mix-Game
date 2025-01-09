// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MixAssetManager.h"
#include "MixCreature.h"
#include "MixGameplayTags.h"
#include "Data/Attribute/MixHeroAttributeData.h"
#include "UI/HeadUI/MixHeadUIWidget.h"
#include "UObject/Object.h"
#include "MixAttribute.generated.h"

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

public:
	template <typename DataClass>
	void Init(AMixCreature* Creature, const TSoftObjectPtr<UDataTable>& DataTablePtr)
	{
		const UDataTable* AttributeDT = UMixAssetManager::Get().GetAssetSync(DataTablePtr);
		if (!ensure(AttributeDT)) return;

		FString CreatureName = MixGameplayTags::GetLastNameFromGameplayTag(Creature->GetCreatureName());
		DataClass* AttributeData = AttributeDT->FindRow<DataClass>(FName(*CreatureName), "AttributeData");
		InitAttributes(Creature, AttributeDT, AttributeData);

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

		if (TIsSame<DataClass, FMixHeroAttributeData>::Value)
		{
			InitChildAttributes(Creature, AttributeDT, static_cast<const FMixHeroAttributeData*>(AttributeData));
		}
	}
	
	virtual void InitChildAttributes(AMixCreature* Creature, const UDataTable* AttributeDT, const FMixHeroAttributeData* AttributeData) {}

public:
	void ApplyHealth(int32 Val);

	void Death() const;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMixOnDeath);
	UPROPERTY(BlueprintAssignable)
	FMixOnDeath OnDeath;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMixOnApplyHealth, int32, ApplyVal, int32, Health, int32, MaxHealth);
	UPROPERTY(BlueprintAssignable)
	FMixOnApplyHealth OnApplyHealth;
};