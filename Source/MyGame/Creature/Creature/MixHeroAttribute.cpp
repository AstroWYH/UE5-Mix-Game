// Fill out your copyright notice in the Description page of Project Settings.

#include "MixHeroAttribute.h"

#include "Creature/Controller/MixHeroControllerFix.h"

void UMixHeroAttribute::ApplyHealth(AMixCreature* Attacker, int32 Val)
{
	Super::ApplyHealth(Attacker, Val);

	AMixAIController* AIController = Cast<AMixHeroControllerFix>(OwnerCreature->GetController());
	if (!AIController) return;

	AIController->SetAttacker(Attacker);
}
