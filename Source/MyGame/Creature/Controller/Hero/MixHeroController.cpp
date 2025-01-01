// Fill out your copyright notice in the Description page of Project Settings.


#include "MixHeroController.h"
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
#include "Creature/Creature/Hero/MixHeroInfoBase.h"
#include "Creature/Creature/Hero/MixHeroInfo_Ashe.h"
#include "MixGameplayTags.h"

void AMixHeroController::Move(const FInputActionValue& Value)
{
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
}

void AMixHeroController::Look(const FInputActionValue& Value)
{
	// // input is a Vector2D
	// FVector2D LookAxisVector = Value.Get<FVector2D>();
	//
	// if (Controller != nullptr)
	// {
	// 	// add yaw and pitch input to controller
	// 	AddControllerYawInput(LookAxisVector.X);
	// 	AddControllerPitchInput(LookAxisVector.Y);
	// }
}

void AMixHeroController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// // Jumping
		// EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMixHeroController::Jump);
		// EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMixHeroController::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMixHeroController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMixHeroController::Look);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this,
		                                   &AMixHeroController::PreNormalAttack);
		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Started, this,
		                                   &AMixHeroController::RightClick);
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Started, this,
		                                   &AMixHeroController::LeftClick);

		// EnhancedInputComponent->BindAction(SkillAction_Q, ETriggerEvent::Started, this, &AMixHeroController::Skill,
		//                                    EHeroOperateKey::Q);
		// EnhancedInputComponent->BindAction(SkillAction_W, ETriggerEvent::Started, this, &AMixHeroController::Skill,
		//                                    EHeroOperateKey::W);
		// EnhancedInputComponent->BindAction(SkillAction_E, ETriggerEvent::Started, this, &AMixHeroController::Skill,
		//                                    EHeroOperateKey::E);
		// EnhancedInputComponent->BindAction(SkillAction_R, ETriggerEvent::Started, this, &AMixHeroController::Skill,
		//                                    EHeroOperateKey::R);

		EnhancedInputComponent->BindAction(SkillAction_Q, ETriggerEvent::Started, this,
		                                   &AMixHeroController::PerformAbility, HeroAbilityType_Q);
		EnhancedInputComponent->BindAction(SkillAction_W, ETriggerEvent::Started, this,
		                                   &AMixHeroController::PerformAbility, HeroAbilityType_W);
		EnhancedInputComponent->BindAction(SkillAction_E, ETriggerEvent::Started, this,
		                                   &AMixHeroController::PerformAbility, HeroAbilityType_E);
		EnhancedInputComponent->BindAction(SkillAction_R, ETriggerEvent::Started, this,
		                                   &AMixHeroController::PerformAbility, HeroAbilityType_R);
	}
}

void AMixHeroController::BeginPlay()
{
	// 蓝图中的Event BeginPlay事件会在C++的BeginPlay被调用时触发
	// 如果不调用这句，则蓝图的EventBegin()不会被调用
	Super::BeginPlay();

	// 初始化增强输入DefaultMappingContext
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// 初始化鼠标图像
	InitMouseCursor();

	Hero = Cast<AMixHero>(GetPawn());
	if (!ensure(Hero.IsValid()))
		return;

	WalkPosition = Hero->GetActorLocation();
}

void AMixHeroController::Tick(float DeltaSeconds)
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

void AMixHeroController::InitMouseCursor()
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

void AMixHeroController::PreNormalAttack(const FInputActionValue& Value)
{
	SetMouseCursorWidget(EMouseCursor::Default, CursorAttackWidget);
	HeroOperateKey = EHeroOperateKey::NormalAttack;

	UMixHeroAttackComponent* HostAttackComponent = Cast<UMixHeroAttackComponent>(Hero->CreatureAttackComponent);
	if (!ensure(HostAttackComponent))
		return;

	HostAttackComponent->SetAttackRangeHidden(false);
}

FVector AMixHeroController::GetMouseClickFloorPosition()
{
	// 老式手动的方法，但好像有一点误差
	// 这里只能用GetMousePositionOnViewport()，结果才正确
	// FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	// float Scale = UWidgetLayoutLibrary::GetViewportScale(GetWorld());
	// FVector2D ScreenMousePosition = MousePosition * Scale;
	//
	// FVector CameraWorldPosition;
	// FVector CamerToMouseWorldDirection;
	// UGameplayStatics::DeprojectScreenToWorld(this, ScreenMousePosition, CameraWorldPosition, CamerToMouseWorldDirection);
	//
	// TArray<AActor*> IgnoreActors;
	// FHitResult HitResult;
	// // DefaultEngine.ini配置了编辑器里新增的Cfg，ECC_GameTraceChannel2对应WalkFloor的ObjType
	// TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{ UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel2) };
	// UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), CameraWorldPosition, CamerToMouseWorldDirection * 10000 + CameraWorldPosition, ObjectTypes, false, IgnoreActors, EDrawDebugTrace::None, HitResult, true, FLinearColor::Green);
	//
	// return FVector(HitResult.Location.X, HitResult.Location.Y, 100);

	FHitResult Hit;
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel2, true, Hit);
	ensure(bHitSuccessful);

	return Hit.Location;
}

void AMixHeroController::RightClick(const FInputActionValue& Value)
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("right mouse click")));

	SetMouseCursorWidget(EMouseCursor::Default, CursorDefaultWidget);
	WalkPosition = GetMouseClickFloorPosition();

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, WalkPosition);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, WalkPosition, FRotator::ZeroRotator,
	                                               FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);

	// 打断角色旋转朝向敌方单位
	UMixHeroAttackComponent* HostAttackComponent = Cast<UMixHeroAttackComponent>(Hero->CreatureAttackComponent);
	if (!ensure(HostAttackComponent))
		return;

	HostAttackComponent->bIsRotating = false;
	HostAttackComponent->SetAttackRangeHidden(true);

	Hero->GetHeroInfo()->SetIsRotating(false);
}

void AMixHeroController::LeftClick(const FInputActionValue& Value)
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("left mouse click")));

	if (HeroOperateKey == EHeroOperateKey::NormalAttack)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursorAttack, GetMouseClickFloorPosition(),
		                                               FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true,
		                                               ENCPoolMethod::None, true);

		UMixHeroAttackComponent* HostAttackComponent = Cast<UMixHeroAttackComponent>(Hero->CreatureAttackComponent);
		if (!ensure(HostAttackComponent))
			return;

		HostAttackComponent->LastMouseClickPos = GetMouseClickFloorPosition();
		HostAttackComponent->PreAttack();
		HostAttackComponent->SetAttackRangeHidden(true);
	}
	else if (HeroOperateKey == EHeroOperateKey::Q || HeroOperateKey == EHeroOperateKey::W || HeroOperateKey ==
		EHeroOperateKey::E || HeroOperateKey == EHeroOperateKey::R)
	{
		TObjectPtr<AMixHeroInfoBase> HeroInfo = Hero->GetHeroInfo();
		HeroInfo->Skill(HeroOperateKey);
		HeroInfo->SetSkillCastMousePos(GetMouseClickFloorPosition());
	}

	SetMouseCursorWidget(EMouseCursor::Default, CursorDefaultWidget);
	HeroOperateKey = EHeroOperateKey::NoType;
}

// TODO: 废弃
void AMixHeroController::Skill(const FInputActionValue& Value, EHeroOperateKey SkillKey)
{
	TObjectPtr<AMixHeroInfoBase> HeroInfo = Hero->GetHeroInfo();
	HeroOperateKey = SkillKey;

	if (!HeroInfo->bIntelligentCasting_Q)
	{
		SetMouseCursorWidget(EMouseCursor::Default, CursorAttackWidget);
		return;
	}

	HeroInfo->Skill(SkillKey);
}

void AMixHeroController::PerformAbility(const FInputActionValue& Value, FGameplayTag AbilityType)
{
	UMixAbilityMgr* AbilityMgr = GetGameInstance()->GetSubsystem<UMixAbilityMgr>();
	AbilityMgr->PerformAbility(Hero->GetHeroName(), AbilityType);
}