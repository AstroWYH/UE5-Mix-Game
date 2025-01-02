// Fill out your copyright notice in the Description page of Project Settings.


#include "MixAttribute.h"

void UMixAttribute::ApplyHealth(int32 ApplyVal)
{
	Health += ApplyVal;

	if (Health <= 0)
	{
		Health = 0;
		Death();
	}

	OnApplyHealth.Broadcast(ApplyVal, Health, MaxHealth);
}

void UMixAttribute::Death() const
{
	OnDeath.Broadcast();
}