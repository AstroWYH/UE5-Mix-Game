#include "MixHostAttackComponent.h"
#include "Character\Host\MixHost.h"
#include "Kismet\KismetSystemLibrary.h"

void UMixHostAttackComponent::Attack()
{
	AMixHost* Host = Cast<AMixHost>(GetOwner());
	if (!ensure(Host)) return;

	FVector StartPos = Host->GetActorLocation();
	FVector EndPos = Host->GetActorLocation();
	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> OutHits;

	UKismetSystemLibrary::SphereTraceMulti(GetWorld(), StartPos, EndPos, 100.0f, ETraceTypeQuery::TraceTypeQuery2, false, ActorsToIgnore, EDrawDebugTrace::Persistent, OutHits, true);
}
