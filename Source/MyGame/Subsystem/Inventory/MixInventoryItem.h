#pragma once

class FMixInventoryItem
{
public:
	FMixInventoryItem(int32 InTID, int32 InAmount, int32 InPosIdx) :TID(InTID), Amount(InAmount), PosIdx(InPosIdx){}
	int32 TID = -1;
	int32 Amount = 0;
	int32 PosIdx = 0;

};