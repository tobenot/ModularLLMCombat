// Copyright (c) 2024 tobenot, See LICENSE in the project root for license information.

// Ability/MCClearMonstersItem.cpp

#include "MCItem_ClearMonsters.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Ability/MCInventoryComponent.h"
#include "Combat/Unit/MCMonsterBase.h"
#include "Engine/EngineTypes.h"

void UMCItem_ClearMonsters::Use_Implementation()
{
	Super::Use_Implementation();
	if (BelongInventoryComponent->GetOwner()->HasAuthority())
	{
		FVector PlayerLocation = BelongInventoryComponent->GetOwner()->GetActorLocation(); // 假设使用者的位置就是玩家当前位置
		// 如果我们已经在服务器上了，就直接执行清理逻辑
		ClearMonster(PlayerLocation, ClearRadius);
	}
}

void UMCItem_ClearMonsters::ClearMonster(FVector Location, float Radius)
{
	// 调用SphereTraceMulti进行射线检测
	TArray<FHitResult> OutHits;
	UWorld* World = GetWorld();
	if (World)
	{
		// 检测球形射线的起始和结束位置相同，以创建一个球体
		bool bHit = UKismetSystemLibrary::SphereTraceMulti(
			World,
			Location,          // 起始位置
			Location,          // 结束位置，同起始位置，形成球
			Radius,            // 半径
			UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_WorldDynamic), // 碰撞通道, 通常为可见性
			false,             // bTraceComplex，是否进行复杂碰撞检测
			TArray<AActor*>(), // ActorsToIgnore，此处不忽略任何参与者
			EDrawDebugTrace::None, // DebugType，是否绘制调试类型
			OutHits,          // 检测到的击中结果
			true              // bIgnoreSelf，是否忽略调用者本身
		);

		// 遍历所有击中的结果
		for (const FHitResult& Hit : OutHits)
		{
			AActor* HitActor = Hit.GetActor();
			// 检查击中的Actor是否为AMCMonsterBase或其子类，并且未被销毁
			if (HitActor && IsValid(HitActor) && HitActor->IsA(AMCMonsterBase::StaticClass()))
			{
				HitActor->Destroy();
			}
		}
	}
}

void UMCItem_ClearMonsters::TestAddClearMonstersItem(UObject* Outer, FString Name, float Radius)
{
#if !UE_BUILD_SHIPPING
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(Outer->GetWorld(), 0);
	if(PlayerPawn)
	{
		UMCInventoryComponent* PlayerInventoryComponent = PlayerPawn->FindComponentByClass<UMCInventoryComponent>();
		if(PlayerInventoryComponent)
		{
			// 创建UMCItem_ClearMonsters实例，设置清除半径和名称
			UMCItem_ClearMonsters* NewClearMonsterItem = NewObject<UMCItem_ClearMonsters>(Outer);
			NewClearMonsterItem->SetAbilityName(Name);
			NewClearMonsterItem->SetQuantity(1);
			NewClearMonsterItem->ClearRadius = Radius * 100;
            
			// 将该道具添加到玩家的背包中
			PlayerInventoryComponent->AddAbility(NewClearMonsterItem);
		}else
		{
			UE_LOG(LogTemp, Error, TEXT("玩家身上没有 UMCInventoryComponent"));
		}
	}
#endif
}
