// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "Tag/MixGameplayTags.h"
#include "Creature/Controller/MixControllerInterface.h"

#include "MixHostHeroControllerFix.generated.h"

class UMixAttackComponent;

UCLASS()
class MYGAME_API AMixHostHeroControllerFix : public APlayerController, public IMixControllerInterface
{
	GENERATED_BODY()

private:
	// 鼠标点地板
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UNiagaraSystem* FXCursor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UNiagaraSystem* FXCursorAttack;

	/** MappingContext */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	// 基础行动
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RightClickAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LeftClickAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* StopAction;

	// 技能Action
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SkillAction_Q;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SkillAction_W;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SkillAction_E;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SkillAction_R;

public:
	// 右键行走
	void RightClick(const FInputActionValue& Value);

	// 按A键
	void PrepareAttack(const FInputActionValue& Value);

	// 已按A键时，鼠标左键普攻
	void LeftClick(const FInputActionValue& Value);

	// 技能QWER
	void PerformAbility(const FInputActionValue& Value, FGameplayTag AbilityType);

protected:
	virtual void BeginPlay();

	virtual void SetupInputComponent();

	virtual void Tick(float DeltaSeconds);

public:
	void InitMouseCursor();

	FVector GetMouseClickFloorPosition();

private:
	// TODO:配置表
	const TCHAR* CursorDefaultPath = TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MixGame/UI/MouseCursor/CursorDefault.CursorDefault_C'");
	const TCHAR* CursorAttackPath = TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MixGame/UI/MouseCursor/CursorAttack.CursorAttack_C'");

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MouseCursor", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> CursorDefaultClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MouseCursor", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> CursorAttackClass;

	UPROPERTY()
	UUserWidget* CursorDefaultWidget;

	UPROPERTY()
	UUserWidget* CursorAttackWidget;

public:
	FVector WalkPosition;

	bool bIsWalking = false;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<class AMixHero> Hero;

	FGameplayTag HeroAbilityType_Q = MixGameplayTags::Ability_Type_Q;
	FGameplayTag HeroAbilityType_W = MixGameplayTags::Ability_Type_W;
	FGameplayTag HeroAbilityType_E = MixGameplayTags::Ability_Type_E;
	FGameplayTag HeroAbilityType_R = MixGameplayTags::Ability_Type_R;

	UMixAttackComponent* AttackComponent;

	bool bHasAttackToConsume = false;
};
