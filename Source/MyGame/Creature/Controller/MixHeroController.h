// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MixControllerInterface.h"
#include "MixHeroController.generated.h"

UCLASS()
class MYGAME_API AMixHeroController : public AAIController, public IMixControllerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMixHeroController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};