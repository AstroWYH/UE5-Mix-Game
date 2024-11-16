// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MixCharacter.h"

#include "MixBatman.generated.h"

UCLASS(config=Game)
class MYGAME_API AMixBatman : public AMixCharacter
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
// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AMixCharacter, meta = (AllowPrivateAccess = "true"))
// 	TObjectPtr<class UMixBatmanAttackComponent> BatmanAttackComponent;

};