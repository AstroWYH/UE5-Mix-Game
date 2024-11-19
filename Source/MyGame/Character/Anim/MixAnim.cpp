// Fill out your copyright notice in the Description page of Project Settings.

#include "MixAnim.h"
#include "Character/MixCharacter.h"
#include "Kismet\KismetMathLibrary.h"

void UMixAnim::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    MixCharacter = Cast<AMixCharacter>(TryGetPawnOwner());
}

void UMixAnim::NativeUpdateAnimation(float DeltaTime)
{
    Super::NativeUpdateAnimation(DeltaTime);

    if (MixCharacter.IsValid())
    {
        Speed = UKismetMathLibrary::VSize(MixCharacter->GetVelocity());
    }
}