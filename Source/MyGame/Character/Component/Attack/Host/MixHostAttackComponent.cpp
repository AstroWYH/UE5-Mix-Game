#include "MixHostAttackComponent.h"
#include "Character/Character/Host/MixHost.h"
#include "Kismet\KismetSystemLibrary.h"
#include "Engine\EngineTypes.h"
#include "Character/Character/Batman/MixBatman.h"
#include "Algo/MinElement.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "Character/Controller/Host/MixHostController.h"
#include "Ammo\Host\MixHostAmmo.h"
#include "Engine\AssetManager.h"

UMixHostAttackComponent::UMixHostAttackComponent() : Super()
{
	PrimaryComponentTick.bCanEverTick = true;

	AttackRange = 500.0f;
	KRotationTime = 0.3f;
	AttackMontagePath = TEXT("/Script/Engine.AnimMontage'/Game/MixGame/Character/Host/Animations/Primary_Fire_Med_Montage.Primary_Fire_Med_Montage'");
	AmmoPath = TEXT("/Script/Engine.Blueprint'/Game/MixGame/Ammo/HostAmmo/HostArrow.HostArrow_C'");
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

bool UMixHostAttackComponent::SelectTarget()
{
	// 获取范围内敌方单位
	BatmanInRange.Empty();
	FVector StartPos = Host->GetActorLocation();
	FVector EndPos = Host->GetActorLocation();
	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> OutHits;
	// DefaultEngine.ini配置了编辑器里新增的Cfg，ECC_GameTraceChannel1对应Enemy的ObjType
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{ UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1) };
	UKismetSystemLibrary::CapsuleTraceMultiForObjects(GetWorld(), StartPos, EndPos, AttackRange, 1000.0f, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);

	for (const FHitResult& Hit : OutHits)
	{
		AActor* HitActor = Hit.GetActor();
		if (!ensure(HitActor)) return false;

		AMixBatman* Batman = Cast<AMixBatman>(HitActor);
		if (!ensure(Batman)) return false;

		BatmanInRange.Add(Batman);
	}

	// 范围内没有敌方单位，禁止攻击
	if (BatmanInRange.IsEmpty()) return false;

	// 筛选范围内最近敌方单位，准备攻击
	SelectCharacterTarget = SelectClosestTarget();
	if (!ensure(SelectCharacterTarget.IsValid())) return false;

	return true;
}

void UMixHostAttackComponent::StopMovement()
{
	// 停止角色位移
	AMixHostController* HostController = Cast<AMixHostController>(Host->GetController());
	if (!ensure(HostController)) return;

	HostController->WalkPosition = Host->GetActorLocation();
	HostController->StopMovement();
}

void UMixHostAttackComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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

void UMixHostAttackComponent::AttackSpawn()
{
	// 资源加载存在多种方式，一般资源类，可以采取LoadObject（同步），采取FStreamableManager.RequestAsyncLoad（异步）
	// 蓝图类，也可以采取FStreamableManager.RequestAsyncLoad（异步），也可以采取TSubClassOf()的存放，然后同步或异步加载
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	StreamableManager.RequestAsyncLoad(AmmoPath, FStreamableDelegate::CreateLambda([this]()
		{
			UClass* AmmoClass = Cast<UClass>(AmmoPath.TryLoad());
			if (!ensure(AmmoClass)) return;

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
			AMixHostAmmo* SpawnedActor = GetWorld()->SpawnActor<AMixHostAmmo>(AmmoClass, BowEmitterTransform, SpawnParams);
		}));
}

