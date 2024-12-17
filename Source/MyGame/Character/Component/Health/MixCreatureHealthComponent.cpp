#include "MixCreatureHealthComponent.h"

void UMixCreatureHealthComponent::TakeDamage(int32 DamageVal)
{
	CurHealth -= DamageVal;

	if (CurHealth <= 0)
	{
		CurHealth = 0;
		Death();
	}

	OnCharacterTakeDamage.Broadcast(DamageVal, CurHealth, MaxHealth);
}

void UMixCreatureHealthComponent::Death()
{
	OnCharacterDeath.Broadcast();
}