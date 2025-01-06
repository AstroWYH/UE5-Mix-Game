// Fill out your copyright notice in the Description page of Project Settings.


#include "MixHostHeroController.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MixGameplayTags.h"
#include "Blueprint\UserWidget.h"
#include "Blueprint\WidgetLayoutLibrary.h"
#include "Kismet\GameplayStatics.h"
#include "Creature/Creature/Hero/MixHero.h"
#include "Engine\EngineTypes.h"
#include "Creature/Component/Attack/Hero/MixHeroAttackComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Ability/MixAbilityMgr.h"
#include "MixGameplayTags.h"
#include "Creature/Component/MixAttackComponent.h"

// void AMixHostHeroController::Move(const FInputActionValue& Value)
// {
// // input is a Vector2D
// FVector2D MovementVector = Value.Get<FVector2D>();
//
// if (Controller != nullptr)
// {
// 	// find out which way is forward
// 	const FRotator Rotation = Controller->GetControlRotation();
// 	const FRotator YawRotation(0, Rotation.Yaw, 0);
//
// 	// get forward vector
// 	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
//
// 	// get right vector
// 	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
//
// 	// add movement
// 	AddMovementInput(ForwardDirection, MovementVector.Y);
// 	AddMovementInput(RightDirection, MovementVector.X);
// }
// }

// void AMixHostHeroController::Look(const FInputActionValue& Value)
// {
// // input is a Vector2D
// FVector2D LookAxisVector = Value.Get<FVector2D>();
//
// if (Controller != nullptr)
// {
// 	// add yaw and pitch input to controller
// 	AddControllerYawInput(LookAxisVector.X);
// 	AddControllerPitchInput(LookAxisVector.Y);
// }
// }

void AMixHostHeroController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// // Jumping
		// EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMixHostHeroController::Jump);
		// EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMixHostHeroController::StopJumping);

		// EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMixHostHeroController::Move);
		// EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMixHostHeroController::Look);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AMixHostHeroController::PrepareAttack);
		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Started, this, &AMixHostHeroController::RightClick);
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Started, this, &AMixHostHeroController::LeftClick);

		EnhancedInputComponent->BindAction(SkillAction_Q, ETriggerEvent::Started, this, &AMixHostHeroController::PerformAbility, HeroAbilityType_Q);
		EnhancedInputComponent->BindAction(SkillAction_W, ETriggerEvent::Started, this, &AMixHostHeroController::PerformAbility, HeroAbilityType_W);
		EnhancedInputComponent->BindAction(SkillAction_E, ETriggerEvent::Started, this, &AMixHostHeroController::PerformAbility, HeroAbilityType_E);
		EnhancedInputComponent->BindAction(SkillAction_R, ETriggerEvent::Started, this, &AMixHostHeroController::PerformAbility, HeroAbilityType_R);
	}
}

void AMixHostHeroController::BeginPlay()
{
	// 蓝图中的Event BeginPlay事件会在C++的BeginPlay被调用时触发
	// 如果不调用这句，则蓝图的EventBegin()不会被调用
	Super::BeginPlay();

	// 初始化增强输入DefaultMappingContext
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// 初始化鼠标图像
	InitMouseCursor();

	Hero = Cast<AMixHero>(GetPawn());
	if (!ensure(Hero.IsValid())) return;

	AttackComponent = Hero->GetAttackComponent();
	ensure(AttackComponent);

	// 获取初始位置
	WalkPosition = Hero->GetActorLocation();
}

void AMixHostHeroController::Tick(float DeltaSeconds)
{
	// if (!ensure(Hero.IsValid())) return;
	//
	// FVector HostPos = Hero->GetActorLocation();
	// FVector HostPosPoint = FVector(HostPos.X, HostPos.Y, 100);
	// float Distance = FVector::Distance(HostPosPoint, WalkPosition);
	//
	// // 20很重要，如果是5，就会一直想走到5以内才停止，就会一直自动转向，因为5 is hard, 20 is relax
	// if (Distance > 20)
	// {
	// 	bIsWalking = true;
	// 	FVector Direction = (WalkPosition - HostPosPoint).GetSafeNormal();
	// 	Hero->AddMovementInput(Direction);
	// }
	// else
	// {
	// 	bIsWalking = false;
	// }
}

void AMixHostHeroController::InitMouseCursor()
{
	// 创建默认鼠标图像
	CursorDefaultClass = FindObject<UClass>(nullptr, CursorDefaultPath);
	if (!CursorDefaultClass.Get())
	{
		CursorDefaultClass = LoadObject<UClass>(nullptr, CursorDefaultPath);
	}
	CursorDefaultWidget = UUserWidget::CreateWidgetInstance(*this, CursorDefaultClass, TEXT("CursorDefault"));
	SetMouseCursorWidget(EMouseCursor::Default, CursorDefaultWidget);

	// 创建攻击鼠标图像
	CursorAttackClass = FindObject<UClass>(nullptr, CursorAttackPath);
	if (!CursorAttackClass.Get())
	{
		CursorAttackClass = LoadObject<UClass>(nullptr, CursorAttackPath);
	}
	CursorAttackWidget = UUserWidget::CreateWidgetInstance(*this, CursorAttackClass, TEXT("CursorAttack"));
}

void AMixHostHeroController::PrepareAttack(const FInputActionValue& Value)
{
	SetMouseCursorWidget(EMouseCursor::Default, CursorAttackWidget);

	// 玩家按A键，显示绿色攻击范围
	AttackComponent->SetAttackRangeHidden(false);
	bHasAttackToConsume = true;
}

FVector AMixHostHeroController::GetMouseClickFloorPosition()
{
	// 老式手动的方法，但好像有一点误差
	// 这里只能用GetMousePositionOnViewport()，结果才正确
	// FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	// float Scale = UWidgetLayoutLibrary::GetViewportScale(GetWorld());
	// FVector2D ScreenMousePosition = MousePosition * Scale;
	//
	// FVector CameraWorldPosition;
	// FVector CamerToMouseWorldDirection;
	// UGameplayStatics::DeprojectScreenToWorld(this, ScreenMousePosition, CameraWorldPosition,
	//                                          CamerToMouseWorldDirection);
	//
	// TArray<AActor*> IgnoreActors;
	// FHitResult HitResult;
	// DefaultEngine.ini配置了编辑器里新增的Cfg，ECC_GameTraceChannel2对应WalkFloor的ObjType
	// TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{
	// 	UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel2)};
	// UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), CameraWorldPosition,
	//                                                 CamerToMouseWorldDirection * 10000 + CameraWorldPosition,
	//                                                 ObjectTypes, false, IgnoreActors, EDrawDebugTrace::None, HitResult,
	//                                                 true, FLinearColor::Green);
	//
	// return FVector(HitResult.Location.X, HitResult.Location.Y, 100);

	FHitResult Hit;
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel2, true, Hit);
	ensure(bHitSuccessful);

	return Hit.Location;
}

void AMixHostHeroController::RightClick(const FInputActionValue& Value)
{
	SetMouseCursorWidget(EMouseCursor::Default, CursorDefaultWidget);
	bHasAttackToConsume = false;
	WalkPosition = GetMouseClickFloorPosition();

	// 很好用的函数，能驱动普通的AController位移
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, WalkPosition);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, WalkPosition, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);

	// 打断普攻旋转
	AttackComponent->SetIsRotating(false);
	AttackComponent->SetAttackRangeHidden(true);

	// 打断技能旋转
	UMixAbilityMgr* AbilityMgr = GetGameInstance()->GetSubsystem<UMixAbilityMgr>();
	AbilityMgr->SetNeedRotate(Hero.Get(), false);
}

void AMixHostHeroController::LeftClick(const FInputActionValue& Value)
{
	SetMouseCursorWidget(EMouseCursor::Default, CursorDefaultWidget);

	if (bHasAttackToConsume)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursorAttack, GetMouseClickFloorPosition(), FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
		AttackComponent->PrepareAttack(GetMouseClickFloorPosition());
		AttackComponent->SetAttackRangeHidden(true);
	}

	bHasAttackToConsume = false;
}

void AMixHostHeroController::PerformAbility(const FInputActionValue& Value, FGameplayTag AbilityType)
{
	UMixAbilityMgr* AbilityMgr = GetGameInstance()->GetSubsystem<UMixAbilityMgr>();
	if (!ensure(AbilityMgr)) return;

	AbilityMgr->PrepareAbility(Hero.Get(), AbilityType, GetMouseClickFloorPosition());
}
