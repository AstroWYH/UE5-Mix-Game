#pragma once

#include "CoreMinimal.h"
#include "MixInventoryItem.generated.h"

UCLASS(BlueprintType)
class MYGAME_API UMixInventoryItem : public UObject
{
	GENERATED_BODY()

public:
	// ��Ҫ��UObject����Ū����
	// UMixInventoryItem();
	// UMixInventoryItem(int32 InTID, int32 InAmount, int32 InPosIdx) :TID(InTID), Amount(InAmount), PosIdx(InPosIdx) {}

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	int32 TID = -1;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	int32 Amount = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	int32 PosIdx = 0;

	void Init(int32 InTID, int32 InAmount, int32 InPosIdx);

};