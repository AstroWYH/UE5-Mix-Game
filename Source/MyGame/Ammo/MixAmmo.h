// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MixAmmo.generated.h"

UCLASS()
class MYGAME_API AMixAmmo : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMixAmmo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AMixAmmo", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class UFloatingPawnMovement> FloatingPawnMovement;

public:
	UFUNCTION(BlueprintCallable, Category = "AMixAmmo")
	virtual void HitTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	TWeakObjectPtr<AActor> Target;

	TWeakObjectPtr<AActor> Shooter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMixAmmo", meta = (AllowPrivateAccess = "true"))
	float AmmoOffset = 0.0f;

	struct FTimerHandle DestroyTimerHandle;

};
