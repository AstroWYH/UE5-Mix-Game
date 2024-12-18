#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "MixData.generated.h" 

USTRUCT(BlueprintType)
struct FMixItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;

};
