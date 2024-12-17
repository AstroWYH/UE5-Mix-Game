// Fill out your copyright notice in the Description page of Project Settings.

#include "MixAnim.h"
#include "Character/MixCreature.h"
#include "Kismet\KismetMathLibrary.h"

void UMixAnim::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    Creature = Cast<AMixCreature>(TryGetPawnOwner());
}

void UMixAnim::NativeUpdateAnimation(float DeltaTime)
{
    Super::NativeUpdateAnimation(DeltaTime);

    if (Creature.IsValid())
    {
        Speed = UKismetMathLibrary::VSize(Creature->GetVelocity());
    }
}