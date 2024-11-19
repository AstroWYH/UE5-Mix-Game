#pragma once

#include "UObject/Interface.h"
#include "MixUIPersistantInterface.generated.h"

class MixUIPersistantInterface
{
public:
};

UINTERFACE(Blueprintable)
class MYGAME_API UMixUIPersistantInterface : public UInterface
{
	GENERATED_BODY()
};

class MYGAME_API IMixUIPersistantInterface : public IInterface
{
	GENERATED_BODY()

public:
	void RegisterSelf()
	{
		if (!UIPersistantList.Contains(this))
		{
			UIPersistantList.Add(this);
		}
	}

	virtual void CreateUI() = 0;

public:
	static TSet<IMixUIPersistantInterface*>& GetUIPersistantList() { return UIPersistantList; }

private:
	inline static TSet<IMixUIPersistantInterface*> UIPersistantList;
};