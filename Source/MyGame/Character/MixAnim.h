// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "MixAnim.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMixAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	float Speed = 0.0f;

	void NativeInitializeAnimation();

	void NativeUpdateAnimation(float DeltaTime);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	TWeakObjectPtr<class AMixCharacter> MixCharacter;

};
