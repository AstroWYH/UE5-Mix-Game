#include "MixHeroAttackComponent.h"

#include "MixAssetManager.h"
#include "Creature/Creature/Hero/MixHero.h"
#include "Kismet\KismetSystemLibrary.h"
#include "Engine\EngineTypes.h"
#include "Creature/Creature/Batman/MixBatman.h"
#include "Algo/MinElement.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "Creature/Controller/Hero/MixHostHeroController.h"
#include "Creature/Ammo/Hero/MixHeroAmmo.h"
#include "Engine\AssetManager.h"

UMixHeroAttackComponent::UMixHeroAttackComponent() : Super()
{
	PrimaryComponentTick.bCanEverTick = true;

	AttackRange = 500.0f;
	KRotationTime = 0.3f;

	// TODO: 配置表
	AttackMontagePath = TEXT(
		"/Script/Engine.AnimMontage'/Game/MixGame/Character/Host/Animations/Primary_Fire_Med_Montage.Primary_Fire_Med_Montage'");
	AmmoPath = TEXT("/Script/Engine.Blueprint'/Game/MixGame/Ammo/HostAmmo/HostArrow.HostArrow_C'");
}

void UMixHeroAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	Hero = Cast<AMixHero>(Creature);
}

TWeakObjectPtr<AMixBatman> UMixHeroAttackComponent::SelectClosestTarget()
{
	FVector HostPos = Hero->GetActorLocation();
	FVector HostPosPoint = FVector(HostPos.X, HostPos.Y, 100);

	TWeakObjectPtr<AMixBatman>* ClosestBatman = Algo::MinElementBy(BatmanInRange,
		[this](const TWeakObjectPtr<AMixBatman> Batman)
		{
			return FVector::Distance(
				LastMouseClickPos,
				Batman->GetActorLocation());
		}
	);

	if (!ensure(ClosestBatman)) return nullptr;
	return *ClosestBatman;
}

// 根据鼠标位置来选人
bool UMixHeroAttackComponent::SelectTarget()
{
	// 获取范围内敌方单位
	BatmanInRange.Empty();
	FVector StartPos = Hero->GetActorLocation();
	FVector EndPos = Hero->GetActorLocation();
	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> OutHits;
	// DefaultEngine.ini配置了编辑器里新增的Cfg，ECC_GameTraceChannel1对应Enemy的ObjType
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{
		UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1)
	};
	UKismetSystemLibrary::CapsuleTraceMultiForObjects(GetWorld(), StartPos, EndPos, AttackRange, 1000.0f, ObjectTypes,
		false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);

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
	SelectCreatureTarget = SelectClosestTarget();
	if (!ensure(SelectCreatureTarget.IsValid())) return false;

	return true;
}

void UMixHeroAttackComponent::StopMovement()
{
	// 停止角色位移
	AMixHostHeroController* HostController = Cast<AMixHostHeroController>(Hero->GetController());
	if (!ensure(HostController)) return;

	HostController->WalkPosition = Hero->GetActorLocation();
	HostController->StopMovement();
}

void UMixHeroAttackComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMixHeroAttackComponent::SetAttackRangeHidden(bool bHidden)
{
	TArray<UActorComponent*> TaggedComponents = Hero->GetComponentsByTag(
		UActorComponent::StaticClass(), "AttackRangeComponent");
	for (UActorComponent* AttackRangeComponent : TaggedComponents)
	{
		if (!ensure(AttackRangeComponent)) continue;
		UStaticMeshComponent* AttackRangeMeshComponent = Cast<UStaticMeshComponent>(AttackRangeComponent);
		if (!ensure(AttackRangeMeshComponent)) continue;

		UE_LOG(LogTemp, Warning, TEXT("Found component with tag %s"), *AttackRangeComponent->GetName());
		AttackRangeMeshComponent->SetHiddenInGame(bHidden);
	}
}

void UMixHeroAttackComponent::AttackSpawn()
{
	// 这段加载逻辑很繁琐，其实UClass直接用UMixAssetMgr加载就行了
	// 资源加载存在多种方式，一般资源类，可以采取LoadObject（同步），采取FStreamableManager.RequestAsyncLoad（异步）
	// 蓝图类，也可以采取FStreamableManager.RequestAsyncLoad（异步），也可以采取TSubClassOf()的存放，然后同步或异步加载

	// TODO: 路径配在AssetMgr蓝图，UClass不需要异步，不需要重复加载
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	StreamableManager.RequestAsyncLoad(AmmoPath, FStreamableDelegate::CreateLambda([this]()
	{
		UClass* AmmoClass = Cast<UClass>(AmmoPath.ResolveObject());
		if (!ensure(AmmoClass)) return;
	
		FTransform BowEmitterTransform = Hero->GetMesh()->GetSocketTransform("BowEmitterSocket");
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = Hero.Get();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.CustomPreSpawnInitalization = [this](AActor* SpawnedActor)
		{
			AMixHeroAmmo* HostAmmo = Cast<AMixHeroAmmo>(SpawnedActor);
			if (!ensure(HostAmmo)) return;
	
			HostAmmo->Target = SelectCreatureTarget;
			HostAmmo->Shooter = Hero;
		};
		AMixHeroAmmo* SpawnedActor = GetWorld()->SpawnActor<AMixHeroAmmo>(AmmoClass, BowEmitterTransform, SpawnParams);
	}));

	// FTransform BowEmitterTransform = Hero->GetMesh()->GetSocketTransform("BowEmitterSocket");
	// FActorSpawnParameters SpawnParams;
	// SpawnParams.Instigator = Hero.Get();
	// SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	// SpawnParams.CustomPreSpawnInitalization = [this](AActor* SpawnedActor)
	// 	{
	// 		AMixHeroAmmo* HostAmmo = Cast<AMixHeroAmmo>(SpawnedActor);
	// 		if (!ensure(HostAmmo)) return;
	//
	// 		HostAmmo->Target = SelectCreatureTarget;
	// 		HostAmmo->Shooter = Hero;
	// 	};
	// AMixHeroAmmo* SpawnedActor = GetWorld()->SpawnActor<AMixHeroAmmo>(UMixAssetManager::Get().NormalAmmo_Ashe_BP, BowEmitterTransform, SpawnParams);
}