#include "MixBatmanAttackComponent.h"
#include "Creature/Creature/Batman/MixBatman.h"
#include "Creature/Controller/Batman/MixAIBatmanController.h"
#include "Kismet\GameplayStatics.h"
#include "Engine\AssetManager.h"
#include "Creature/Ammo/Batman/MixBatmanAmmo.h"

UMixBatmanAttackComponent::UMixBatmanAttackComponent() : Super()
{
	PrimaryComponentTick.bCanEverTick = true;

	AttackRange = 400.0f;
	KRotationTime = 0.5f;
	AttackMontagePath = TEXT(
		"/Script/Engine.AnimMontage'/Game/BattleWizardPolyart/Animations/Attack01Anim_Montage.Attack01Anim_Montage'");
	AmmoPath = TEXT("/Script/Engine.Blueprint'/Game/MixGame/Ammo/BatmanAmmo/BatmanAmmo.BatmanAmmo_C'");
}

void UMixBatmanAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	Batman = Cast<AMixBatman>(Creature);
}

void UMixBatmanAttackComponent::StopMovement()
{
	AMixAIBatmanController* BatmanController = Cast<AMixAIBatmanController>(Batman->GetController());
	if (!ensure(BatmanController)) return;

	BatmanController->StopMovement();
}

bool UMixBatmanAttackComponent::SelectTarget()
{
	// Batman展开攻击时，不需要选人
	SelectCreatureTarget = Cast<AMixCreature>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!ensure(SelectCreatureTarget.IsValid())) return false;

	return true;
}

void UMixBatmanAttackComponent::AttackSpawn()
{
	// TODO: 路径配在AssetMgr蓝图，UClass不需要异步，不需要重复加载
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	StreamableManager.RequestAsyncLoad(AmmoPath, FStreamableDelegate::CreateLambda([this]()
	{
		UClass* AmmoClass = Cast<UClass>(AmmoPath.ResolveObject());
		if (!ensure(AmmoClass)) return;

		TArray<UActorComponent*> TaggedComponents = Batman->GetComponentsByTag(
			UActorComponent::StaticClass(), "LaunchPoint");
		USceneComponent* LaunchPoint = nullptr;
		for (UActorComponent* Component : TaggedComponents)
		{
			if (!ensure(Component)) continue;
			LaunchPoint = Cast<USceneComponent>(Component);
			if (!ensure(LaunchPoint)) continue;
		}

		FTransform EmitterTransform = LaunchPoint->GetComponentToWorld();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = Batman.Get();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.CustomPreSpawnInitalization = [this](AActor* SpawnedActor)
		{
			AMixBatmanAmmo* BatmanAmmo = Cast<AMixBatmanAmmo>(SpawnedActor);
			if (!ensure(BatmanAmmo)) return;

			BatmanAmmo->Target = SelectCreatureTarget;
			BatmanAmmo->Shooter = Batman;
		};
		AMixBatmanAmmo* SpawnedActor = GetWorld()->SpawnActor<AMixBatmanAmmo>(AmmoClass, EmitterTransform, SpawnParams);
	}));
}