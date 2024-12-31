#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "MixItemAsset.generated.h"

USTRUCT(BlueprintType)
struct FMixItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 TID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTexture2D* Icon;

};
