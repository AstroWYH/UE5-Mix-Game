#include "MixBatmanAttackComponent.h"
#include "Character\Batman\MixBatman.h"
#include "Character\Batman\MixAIBatmanController.h"
#include "Kismet\GameplayStatics.h"

UMixBatmanAttackComponent::UMixBatmanAttackComponent() : Super()
{
	PrimaryComponentTick.bCanEverTick = true;

	AttackRange = 300.0f;
	KRotationTime = 0.5f;
}

void UMixBatmanAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	Batman = Cast<AMixBatman>(MixCharacter);
}

void UMixBatmanAttackComponent::StopMovement()
{
	AMixAIBatmanController* BatmanController = Cast<AMixAIBatmanController>(Batman->GetController());
	if (!ensure(BatmanController)) return;

	BatmanController->StopMovement();
}

void UMixBatmanAttackComponent::SelectTarget()
{
	SelectCharacterTarget = Cast<AMixCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!ensure(SelectCharacterTarget.IsValid())) return;
}

