#pragma once

#include "UObject/Interface.h"
#include "MixUIPersistantInterface.generated.h"

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

	void UnRegisterSelf()
	{
		UIPersistantList.Remove(this);
	}

	virtual void LoadUIClass() = 0;

	virtual void CreateUI() = 0;

	virtual void BindUIEvent() = 0;

public:
	static TSet<IMixUIPersistantInterface*>& GetUIPersistantList() { return UIPersistantList; }

private:
	static TSet<IMixUIPersistantInterface*> UIPersistantList;
};