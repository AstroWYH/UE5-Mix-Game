// Fill out your copyright notice in the Description page of Project Settings.


#include "MixHostController.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint\UserWidget.h"
#include "Blueprint\WidgetLayoutLibrary.h"
#include "Kismet\GameplayStatics.h"
#include "Character\Host\MixHost.h"
#include "Engine\EngineTypes.h"

void AMixHostController::Move(const FInputActionValue& Value)
{
	/*
		// input is a Vector2D
		FVector2D MovementVector = Value.Get<FVector2D>();

		if (Controller != nullptr)
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			// get right vector
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			// add movement
			AddMovementInput(ForwardDirection, MovementVector.Y);
			AddMovementInput(RightDirection, MovementVector.X);
		}*/
}

void AMixHostController::Look(const FInputActionValue& Value)
{
	/*
		// input is a Vector2D
		FVector2D LookAxisVector = Value.Get<FVector2D>();

		if (Controller != nullptr)
		{
			// add yaw and pitch input to controller
			AddControllerYawInput(LookAxisVector.X);
			AddControllerPitchInput(LookAxisVector.Y);
		}*/
}

void AMixHostController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {

		// Jumping
		// EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMixHostController::Jump);
		// EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMixHostController::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMixHostController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMixHostController::Look);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AMixHostController::Attack);
		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Started, this, &AMixHostController::RightClick);
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Started, this, &AMixHostController::LeftClick);
	}
}

void AMixHostController::BeginPlay()
{
	// ��ͼ�е�Event BeginPlay�¼�����C++��BeginPlay������ʱ����
	// �����������䣬����ͼ��EventBegin()���ᱻ����
	Super::BeginPlay();

	// ��ʼ����ǿ����DefaultMappingContext
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// ��ʼ�����ͼ��
	InitMouseCursor();

	Host = Cast<AMixHost>(GetPawn());
	if (!ensure(Host.IsValid())) return;

	WalkPosition = Host->GetActorLocation();
}

void AMixHostController::Tick(float DeltaSeconds)
{
	if (!ensure(Host.IsValid())) return;

	FVector HostPos = Host->GetActorLocation();
	FVector HostPosPoint = FVector(HostPos.X, HostPos.Y, 100);
	float Distance = FVector::Distance(HostPosPoint, WalkPosition);

	// 20����Ҫ�������5���ͻ�һֱ���ߵ�5���ڲ�ֹͣ���ͻ�һֱ�Զ�ת����Ϊ5 is hard, 20 is relax
	if (Distance > 20)
	{
		bIsWalking = true;
		FVector Direction = (WalkPosition - HostPosPoint).GetSafeNormal();
		Host->AddMovementInput(Direction);
	}
	else
	{
		bIsWalking = false;
	}
}

void AMixHostController::InitMouseCursor()
{
	// ����Ĭ�����ͼ��
	CursorDefaultClass = FindObject<UClass>(nullptr, CursorDefaultPath);
	if (!CursorDefaultClass.Get())
	{
		CursorDefaultClass = LoadObject<UClass>(nullptr, CursorDefaultPath);
	}
	CursorDefaultWidget = UUserWidget::CreateWidgetInstance(*this, CursorDefaultClass, TEXT("CursorDefault"));
	SetMouseCursorWidget(EMouseCursor::Default, CursorDefaultWidget);

	// �����������ͼ��
	CursorAttackClass = FindObject<UClass>(nullptr, CursorAttackPath);
	if (!CursorAttackClass.Get())
	{
		CursorAttackClass = LoadObject<UClass>(nullptr, CursorAttackPath);
	}
	CursorAttackWidget = UUserWidget::CreateWidgetInstance(*this, CursorAttackClass, TEXT("CursorAttack"));
}

void AMixHostController::Attack(const FInputActionValue& Value)
{
	SetMouseCursorWidget(EMouseCursor::Default, CursorAttackWidget);
	bPrepareAttack = true;
}

FVector AMixHostController::GetMouseClickFloorPosition()
{
	// ����ֻ����GetMousePositionOnViewport()���������ȷ
	FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	float Scale = UWidgetLayoutLibrary::GetViewportScale(GetWorld());
	FVector2D ScreenMousePosition = MousePosition * Scale;

	FVector CameraWorldPosition;
	FVector CamerToMouseWorldDirection;
	UGameplayStatics::DeprojectScreenToWorld(this, ScreenMousePosition, CameraWorldPosition, CamerToMouseWorldDirection);

	TArray<AActor*> IgnoreActors;
	FHitResult HitResult;
	// DefaultEngine.ini�����˱༭����������Cfg��ECC_GameTraceChannel2��ӦWalkFloor��ObjType
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{ UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel2) };
	UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), CameraWorldPosition, CamerToMouseWorldDirection * 10000 + CameraWorldPosition, ObjectTypes, false, IgnoreActors, EDrawDebugTrace::None, HitResult, true, FLinearColor::Green);

	return FVector(HitResult.Location.X, HitResult.Location.Y, 100);
}

void AMixHostController::RightClick(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("right mouse click")));

	SetMouseCursorWidget(EMouseCursor::Default, CursorDefaultWidget);
	WalkPosition = GetMouseClickFloorPosition();
}

void AMixHostController::LeftClick(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("left mouse click")));

	if (bPrepareAttack)
	{
		bPrepareAttack = false;
		SetMouseCursorWidget(EMouseCursor::Default, CursorDefaultWidget);

		UMixCharacterAttackComponent* AttackComponent = Host->FindComponentByClass<UMixCharacterAttackComponent>();
		if (!ensure(AttackComponent)) return;

		AttackComponent->Attack(GetMouseClickFloorPosition());
	}
}
