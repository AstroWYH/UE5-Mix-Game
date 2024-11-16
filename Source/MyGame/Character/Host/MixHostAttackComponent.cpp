#include "MixHostAttackComponent.h"
#include "Character\Host\MixHost.h"
#include "Kismet\KismetSystemLibrary.h"
#include "Engine\EngineTypes.h"
#include "Character\Batman\MixBatman.h"
#include "Algo/MinElement.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "Character\Host\MixHostController.h"
#include "Engine\AssetManager.h"
#include "Ammo\Host\MixHostAmmo.h"

UMixHostAttackComponent::UMixHostAttackComponent() : Super()
{
	PrimaryComponentTick.bCanEverTick = true;

	AttackRange = 500.0f;
	KRotationTime = 0.3f;
}

void UMixHostAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	Host = Cast<AMixHost>(MixCharacter);
}

TWeakObjectPtr<AMixBatman> UMixHostAttackComponent::SelectClosestTarget()
{
	FVector HostPos = Host->GetActorLocation();
	FVector HostPosPoint = FVector(HostPos.X, HostPos.Y, 100);

	TWeakObjectPtr<AMixBatman>* ClosestBatman = Algo::MinElementBy(BatmanInRange,
		[this](const TWeakObjectPtr<AMixBatman> Batman)
		{
			return FVector::Distance(LastMouseClickPos, Batman->GetActorLocation());
		}
	);

	if (!ensure(ClosestBatman)) return nullptr;
	return *ClosestBatman;
}

void UMixHostAttackComponent::SelectTarget()
{
	// ��ȡ��Χ�ڵз���λ
	BatmanInRange.Empty();
	FVector StartPos = Host->GetActorLocation();
	FVector EndPos = Host->GetActorLocation();
	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> OutHits;
	// DefaultEngine.ini�����˱༭����������Cfg��ECC_GameTraceChannel1��ӦEnemy��ObjType
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{ UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1) };
	UKismetSystemLibrary::CapsuleTraceMultiForObjects(GetWorld(), StartPos, EndPos, AttackRange, 1000.0f, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);

	for (const FHitResult& Hit : OutHits)
	{
		AActor* HitActor = Hit.GetActor();
		if (!ensure(HitActor)) return;

		AMixBatman* Batman = Cast<AMixBatman>(HitActor);
		if (!ensure(Batman)) return;

		BatmanInRange.Add(Batman);
	}

	// ��Χ��û�ез���λ����ֹ����
	if (BatmanInRange.IsEmpty()) return;

	// ɸѡ��Χ������з���λ��׼������
	SelectCharacterTarget = SelectClosestTarget();
	if (!ensure(SelectCharacterTarget.IsValid())) return;
}

void UMixHostAttackComponent::StopMovement()
{
	// ֹͣ��ɫλ��
	AMixHostController* HostController = Cast<AMixHostController>(Host->GetController());
	if (!ensure(HostController)) return;
	HostController->WalkPosition = Host->GetActorLocation();
	HostController->StopMovement();
}

void UMixHostAttackComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsRotating)
	{
		FRotator HostNewRotation = FRotator(0.0f, Host->GetActorRotation().Yaw + YawPerFrame, 0.0f);
		Host->SetActorRotation(HostNewRotation);

		float RotationDiff = FMath::Abs(FMath::Fmod(SelfLookAtRotation.Yaw - HostNewRotation.Yaw + 180.0f, 360.0f) - 180.0f);
		if (RotationDiff <= 6.0f)
		{
			// ����ȡHost����Ӧ�õĳ������ڽ���
			FRotator FinalFixRotation = FRotator(0.0f, (SelectCharacterTarget->GetActorLocation() - Host->GetActorLocation()).Rotation().Yaw, 0.0f);
			Host->SetActorRotation(FinalFixRotation);
			bIsRotating = false;

			PlayAttackMontage();
		}
	}
}

void UMixHostAttackComponent::PlayAttackMontage()
{
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	StreamableManager.RequestAsyncLoad(AttackMontagePath, FStreamableDelegate::CreateLambda([this]()
		{
			UAnimMontage* AttackAnimMontage = Cast<UAnimMontage>(AttackMontagePath.TryLoad());
			if (!ensure(AttackAnimMontage)) return;

			Host->PlayAnimMontage(AttackAnimMontage);
// 			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("play attack montage")));
		}));
}

void UMixHostAttackComponent::AttackSpawn()
{
	// ��Դ���ش��ڶ��ַ�ʽ��һ����Դ�࣬���Բ�ȡLoadObject��ͬ��������ȡFStreamableManager.RequestAsyncLoad���첽��
	// ��ͼ�࣬Ҳ���Բ�ȡFStreamableManager.RequestAsyncLoad���첽����Ҳ���Բ�ȡTSubClassOf()�Ĵ�ţ�Ȼ��ͬ�����첽����
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	StreamableManager.RequestAsyncLoad(ArrowAmmoPath, FStreamableDelegate::CreateLambda([this]()
		{
			UClass* ArrowAmmoClass = Cast<UClass>(ArrowAmmoPath.TryLoad());
			if (!ensure(ArrowAmmoClass)) return;
		
			FTransform BowEmitterTransform = Host->GetMesh()->GetSocketTransform("BowEmitterSocket");
			FActorSpawnParameters SpawnParams;
			SpawnParams.Instigator = Host.Get();
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParams.CustomPreSpawnInitalization = [this](AActor* SpawnedActor)
				{
					AMixHostAmmo* HostAmmo = Cast<AMixHostAmmo>(SpawnedActor);
					if (!ensure(HostAmmo)) return;

					HostAmmo->Target = SelectCharacterTarget;
					HostAmmo->Shooter = Host;
				};
			AMixHostAmmo* SpawnedActor = GetWorld()->SpawnActor<AMixHostAmmo>(ArrowAmmoClass, BowEmitterTransform, SpawnParams);
		}));
}

void UMixHostAttackComponent::SetAttackRangeHidden(bool bHidden)
{
	TArray<UActorComponent*> TaggedComponents = Host->GetComponentsByTag(UActorComponent::StaticClass(), "AttackRangeComponent");
	for (UActorComponent* AttackRangeComponent : TaggedComponents)
	{
		if (!ensure(AttackRangeComponent)) continue;
		UStaticMeshComponent* AttackRangeMeshComponent = Cast<UStaticMeshComponent>(AttackRangeComponent);
		if (!ensure(AttackRangeMeshComponent)) continue;

		UE_LOG(LogTemp, Warning, TEXT("Found component with tag %s"), *AttackRangeComponent->GetName());
// 		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Found component with tag %s"), *AttackRangeComponent->GetName()));

		AttackRangeMeshComponent->SetHiddenInGame(bHidden);
	}
}
