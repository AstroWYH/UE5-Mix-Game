// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "Creature/Creature/MixCreature.h"

#include "MixHero.generated.h"

class AMixHeroInfoBase;

UCLASS(config=Game)
class MYGAME_API AMixHero : public AMixCreature
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	AMixHero();

protected:
	// APawn interface
	// virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AMixHeroInfoBase> HeroInfo;

public:
	void SetHeroInfo(const TObjectPtr<AMixHeroInfoBase>& InHeroInfo);

	TObjectPtr<AMixHeroInfoBase> GetHeroInfo() const;

private:
	FGameplayTag HeroName;

public:
	FGameplayTag GetHeroName() const
	{
		return HeroName;
	}

	void SetHeroName(const FGameplayTag& InHeroName)
	{
		HeroName = InHeroName;
	}
};