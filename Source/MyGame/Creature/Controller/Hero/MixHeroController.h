// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "MixGameplayTags.h"
#include "Creature/Creature/Hero/MixHeroInfo_Ashe.h"

#include "MixHeroController.generated.h"

UCLASS()
class MYGAME_API AMixHeroController : public APlayerController
{
	GENERATED_BODY()

public:
	// 鼠标指针
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UNiagaraSystem* FXCursor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UNiagaraSystem* FXCursorAttack;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	// 基础移动Action
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RightClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LeftClickAction;

	// 技能Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SkillAction_Q;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SkillAction_W;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SkillAction_E;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SkillAction_R;

public:
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	// 右键行走
	void RightClick(const FInputActionValue& Value);

	// 预普通攻击，按A键
	void PreNormalAttack(const FInputActionValue& Value);

	// 已按A键时，左键普攻
	void LeftClick(const FInputActionValue& Value);

	// 技能Q/W/E/R
	void Skill(const FInputActionValue& Value, EHeroOperateKey SkillKey);

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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MouseCursor")
	TSubclassOf<UUserWidget> CursorDefaultClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MouseCursor")
	TSubclassOf<UUserWidget> CursorAttackClass;

	UPROPERTY()
    UUserWidget* CursorDefaultWidget;

	UPROPERTY()
    UUserWidget* CursorAttackWidget;

public:
	FVector WalkPosition;

	bool bIsWalking = false;

	EHeroOperateKey HeroOperateKey = EHeroOperateKey::NoType;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Controller")
	TWeakObjectPtr<class AMixHero> Hero;

	FGameplayTag Ability_Type_Q = MixGameplayTags::Ability_Type_Q;
	FGameplayTag Ability_Type_W = MixGameplayTags::Ability_Type_W;
	FGameplayTag Ability_Type_E = MixGameplayTags::Ability_Type_E;
	FGameplayTag Ability_Type_R = MixGameplayTags::Ability_Type_R;
};
