#include "MixCharacterHealthComponent.h"

void UMixCharacterHealthComponent::TakeDamage(int32 DamageVal)
{
	CurrentHealth -= DamageVal;

	if (CurrentHealth <= 0)
	{
		CurrentHealth = 0;
		Death();
	}

	OnCharacterTakeDamage.Broadcast(DamageVal);
}

void UMixCharacterHealthComponent::Death()
{
	OnCharacterDeath.Broadcast();
}