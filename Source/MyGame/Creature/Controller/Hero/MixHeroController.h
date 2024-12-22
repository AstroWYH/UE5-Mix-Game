// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"

#include "MixHeroController.generated.h"

/**
 * 
 */
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

	// 普通攻击
	void NormalAttack(const FInputActionValue& Value);

	// 右键行走
	void RightClick(const FInputActionValue& Value);

	// 左键辅助普攻
	void LeftClick(const FInputActionValue& Value);

	// 技能
	void Skill_Q(const FInputActionValue& Value);

	void Skill_W(const FInputActionValue& Value);

	void Skill_E(const FInputActionValue& Value);

	void Skill_R(const FInputActionValue& Value);

protected:
	virtual void BeginPlay();

	virtual void SetupInputComponent();

	virtual void Tick(float DeltaSeconds);

private:
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MouseCursor")
    UUserWidget* CursorDefaultWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MouseCursor")
    UUserWidget* CursorAttackWidget;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Controller")
	FVector WalkPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Controller")
	bool bIsWalking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Controller")
	bool bPrepareAttack = false;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Controller")
	TWeakObjectPtr<class AMixHero> Hero;

};
