#pragma once

#include "CoreMinimal.h"
#include "MixInventorySubsystem.h"
#include "MixItem.generated.h"

UCLASS(BlueprintType)
class MYGAME_API UMixItem : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	int32 TID = -1;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	int32 XID = -1;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	TWeakObjectPtr<UMixItemCfg> ItemCfg = nullptr;

};