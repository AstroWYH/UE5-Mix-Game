#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "MixAttributeData.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FMixAttributeData : public FTableRowBase
{
	GENERATED_BODY()

public:
	// TODO: 后续会扩展生命值表，每级的生命值
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Speed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 AttackVal;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 DefenseVal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 AttackRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 AttackSpeed;

};