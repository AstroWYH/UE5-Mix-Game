// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MixAIController.h"
#include "MixTowerController.generated.h"

UCLASS()
class MYGAME_API AMixTowerController : public AMixAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMixTowerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void FriendHeroUnderAttack(AMixCreature* InEnemyHero, AMixCreature* InFriendHero) override;

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void OnCreatureStepIn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCreatureStepOut(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual AMixCreature* GetClosestTarget() const override;
};