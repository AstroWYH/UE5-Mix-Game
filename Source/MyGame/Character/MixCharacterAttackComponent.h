#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MixCharacterAttackComponent.generated.h"

UCLASS()
class MYGAME_API UMixCharacterAttackComponent : public UActorComponent
{
    GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void Attack(FVector MouseClickPos);

};
