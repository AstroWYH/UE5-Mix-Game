#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character\MixCharacterAttackComponent.h"
#include "MixHostAttackComponent.generated.h"

UCLASS()
class MYGAME_API UMixHostAttackComponent : public UMixCharacterAttackComponent
{
    GENERATED_BODY()

public:    
     UFUNCTION(BlueprintCallable, Category = "Attack")
     void Attack() override;

};
