// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MixAttackComponent.generated.h"


class AMixCreature;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYGAME_API UMixAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMixAttackComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AMixCreature* Creature;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FSoftObjectPath Montage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsRanged = false;

	TSubclassOf<>

public:
	AMixCreature* GetCreature() const
	{
		return Creature;
	}

	void SetCreature(AMixCreature* InCreature)
	{
		this->Creature = InCreature;
	}
};