#include "MixHostAttackComponent.h"
#include "Character\Host\MixHost.h"
#include "Kismet\KismetSystemLibrary.h"
#include "Engine\EngineTypes.h"
#include "Character\Batman\MixBatman.h"
#include "Algo/MinElement.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "Character\Host\MixHostController.h"

UMixHostAttackComponent::UMixHostAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

TWeakObjectPtr<AMixBatman> UMixHostAttackComponent::SelectTarget()
{
	AMixHost* Host = Cast<AMixHost>(GetOwner());
	if (!ensure(Host)) return nullptr;

	FVector HostPos = Host->GetActorLocation();
	FVector HostPosPoint = FVector(HostPos.X, HostPos.Y, 100);

	// 	TWeakObjectPtr<AMixBatman> ClosestBatman = nullptr;
	// 	float FinalDistance = FLT_MAX;
	// 	for (const auto& Batman : BatmanInRange)
	// 	{
	// 		float Distance = FVector::Distance(HostPosPoint, Batman->GetActorLocation());
	// 		if (Distance < FinalDistance)
	// 		{
	// 			FinalDistance = Distance;
	//          ClosestBatman = Batman;
	// 		}
	// 	}

	TWeakObjectPtr<AMixBatman>* ClosestBatman = Algo::MinElementBy(BatmanInRange,
		[HostPosPoint](const TWeakObjectPtr<AMixBatman> Batman)
		{
			return FVector::Distance(HostPosPoint, Batman->GetActorLocation());
		}
	);

	if (!ensure(ClosestBatman)) return nullptr;
	return *ClosestBatman;
}

void UMixHostAttackComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AMixHost* Host = Cast<AMixHost>(GetOwner());
	if (!ensure(Host)) return;

	if (bIsRotating)
	{
		float RotationTime = 0.3f;
		float TotalYawDifference = FMath::Fmod(TargetRotation.Yaw - HostRotation.Yaw + 180.0f, 360.0f) - 180.0f;

		float YawPerFrame = TotalYawDifference / (RotationTime / GetWorld()->GetDeltaSeconds());
		FRotator NewRotation = Host->GetActorRotation();
		NewRotation.Yaw += YawPerFrame;
		Host->SetActorRotation(NewRotation);

		float RotationDifference = FMath::Abs(FMath::Fmod(TargetRotation.Yaw - NewRotation.Yaw + 180.0f, 360.0f) - 180.0f);
		if (RotationDifference <= 6.0f)
		{
			Host->SetActorRotation(TargetRotation);
			bIsRotating = false;
		}
	}
}

void UMixHostAttackComponent::Attack(FVector MouseClickPos)
{
	LastMouseClickPos = MouseClickPos;
	BatmanInRange.Empty();

	// ��ȡ��Χ�ڵз���λ
	AMixHost* Host = Cast<AMixHost>(GetOwner());
	if (!ensure(Host)) return;

	FVector StartPos = Host->GetActorLocation();
	FVector EndPos = Host->GetActorLocation();
	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> OutHits;
	// DefaultEngine.ini�����˱༭����������Cfg��ECC_GameTraceChannel1��ӦEnemy��ObjType
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{ UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1) };
	UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), StartPos, EndPos, AttackRange, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::Persistent, OutHits, true);

    for (const FHitResult& Hit : OutHits)
    {
        AActor* HitActor = Hit.GetActor();
        if (!ensure(HitActor)) return;

		AMixBatman* Batman = Cast<AMixBatman>(HitActor);
		if (!ensure(Batman)) return;

		BatmanInRange.Add(Batman);
    }
	// ��Χ��û�ез���λ���ܾ�����
	if (BatmanInRange.IsEmpty()) return;

	// ɸѡ��Χ������з���λ��׼������
	SelectBatman = SelectTarget();
	if (!ensure(SelectBatman.IsValid())) return;

	// ֹͣ��ɫλ��
	AMixHostController* HostController = Cast<AMixHostController>(Host->GetController());
	if (!ensure(HostController)) return;
	HostController->WalkPosition = Host->GetActorLocation();
	// Host->GetCharacterMovement()->StopMovementImmediately();

	// ����Ŀ����ת
	bIsRotating = true;

// 	ʹ�ö�ʱ����ת��ɫ����з���λ������ɶ�����Ų��Tick()���
// 	FVector HostLocation = Host->GetActorLocation();
// 	FRotator HostRotation = Host->GetActorRotation();
// 	FVector TargetLocation = SelectBatman->GetActorLocation();
// 	FRotator TargetRotation = (TargetLocation - HostLocation).Rotation();
// 
// 	float RotationTime = 0.3f;
// 	float TotalYawDifference = FMath::Fmod(TargetRotation.Yaw - HostRotation.Yaw + 180.0f, 360.0f) - 180.0f;
// 
// 	GetWorld()->GetTimerManager().SetTimer(RotationHandle, [this, Host, HostRotation, TargetRotation, RotationTime, TotalYawDifference]()
// 		{
// 			float YawPerFrame = TotalYawDifference / (RotationTime / GetWorld()->GetDeltaSeconds());
// 			float DeltaTime = GetWorld()->GetDeltaSeconds();
// 			FRotator NewRotation = Host->GetActorRotation();
// 			NewRotation.Yaw += YawPerFrame / 10;
// 			Host->SetActorRotation(NewRotation);
// 
// 			float RotationDifference = FMath::Abs(FMath::Fmod(TargetRotation.Yaw - NewRotation.Yaw + 180.0f, 360.0f) - 180.0f);
// 
// 			if (RotationDifference <= 1.0f)
// 			{
// 				GetWorld()->GetTimerManager().ClearTimer(RotationHandle);
// 			}
// 		}, GetWorld()->GetDeltaSeconds() / 10, true);

// 	HostLocation = Host->GetActorLocation();
// 	HostRotation = Host->GetActorRotation();
// 	TargetLocation = SelectBatman->GetActorLocation();
// 	TargetRotation = (TargetLocation - HostLocation).Rotation();

	HostLocation = Host->GetActorLocation();
	HostRotation = FRotator(0.0f, Host->GetActorRotation().Yaw, 0.0f);
	TargetLocation = SelectBatman->GetActorLocation();
	TargetRotation = FRotator(0.0f, (TargetLocation - HostLocation).Rotation().Yaw, 0.0f);
}

