#include "MixInventoryItem.h"

void UMixInventoryItem::Init(int32 InTID, int32 InAmount, int32 InPosIdx)
{
	TID = InTID;
	Amount = InAmount;
	PosIdx = InPosIdx;
}