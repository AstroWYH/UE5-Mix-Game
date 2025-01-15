// Fill out your copyright notice in the Description page of Project Settings.

#include "MixHeroAttribute.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Creature/Controller/MixHeroControllerFix.h"
#include "Hero/MixHero.h"

void UMixHeroAttribute::ApplyHealth(AMixCreature* Attacker, int32 Val)
{
	Super::ApplyHealth(Attacker, Val);

	AMixHeroControllerFix* HeroController = Cast<AMixHeroControllerFix>(OwnerCreature->GetController());
	if (!HeroController) return;
	if (!Cast<AMixHero>(Attacker)) return;

	// TODO: 暂时只处理AIHero受到Hero伤害
	HeroController->UnderHeroAttack(Attacker);
}
