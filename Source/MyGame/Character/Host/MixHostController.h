// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"

#include "MixHostController.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API AMixHostController : public APlayerController
{
	GENERATED_BODY()

public:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	// ¿∂Õº¿Ô≈‰÷√
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

public:
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Attack(const FInputActionValue& Value);

	void RightClick(const FInputActionValue& Value);

	void LeftClick(const FInputActionValue& Value);

protected:
	virtual void BeginPlay();

	virtual void SetupInputComponent();

	virtual void Tick(float DeltaSeconds);

private:
	void InitMouseCursor();

private:
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Host Controller")
	FVector WalkPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Host Controller")
	bool bIsWalking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Host Controller")
	bool bPrepareAttack = false;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Host Controller")
	TWeakObjectPtr<class AMixHost> Host;

};
