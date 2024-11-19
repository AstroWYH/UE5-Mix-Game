// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Health/MixCharacterHealthComponent.h"
#include "MixHostHealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYGAME_API UMixHostHealthComponent : public UMixCharacterHealthComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMixHostHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,  FActorComponentTickFunction* ThisTickFunction) override;
};
