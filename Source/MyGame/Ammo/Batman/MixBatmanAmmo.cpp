// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo/Batman/MixBatmanAmmo.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Character\Host\MixHost.h"

void AMixBatmanAmmo::BeginPlay()
{
	Super::BeginPlay();

// 	AMixHost* Host = Cast<AMixHost>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
//  	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Host->GetActorLocation());
}
