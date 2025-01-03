#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "MixHeroAttributeData.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FMixHeroAttributeData : public FMixAttributeData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	int32 MaxMagic;

	UPROPERTY(EditDefaultsOnly)
	int32 Experience;

};