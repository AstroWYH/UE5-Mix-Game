#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "MixItemData.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FMixItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	int32 TID;

	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* Icon;

};
