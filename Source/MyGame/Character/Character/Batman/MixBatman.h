// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character/Character/MixCreature.h"

#include "MixBatman.generated.h"

UCLASS(config=Game)
class MYGAME_API AMixBatman : public AMixCreature
{
	GENERATED_BODY()

public:
	AMixBatman();

	void BeginPlay() override;

public:
// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
// 	UStaticMeshComponent* TestMesh;
// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
// 	TObjectPtr<UStaticMeshComponent> TestMesh2;
// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AMixCreature, meta = (AllowPrivateAccess = "true"))
// 	TObjectPtr<class UMixBatmanAttackComponent> BatmanAttackComponent;

};