// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MixRangedAmmo.generated.h"

UCLASS()
class MYGAME_API AMixRangedAmmo : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMixRangedAmmo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<AActor> Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<AActor> Shooter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackVal = 0;

	struct FTimerHandle DestroyTimerHandle;

public:
	// 蓝图调用
	UFUNCTION(BlueprintCallable)
	void CauseDamage(int32 DamageVal);

	// 蓝图实现
	UFUNCTION(BlueprintImplementableEvent)
	virtual void BP_HitTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 蓝图可重载
	UFUNCTION(BlueprintNativeEvent)
	virtual void DestroySelf();
};
