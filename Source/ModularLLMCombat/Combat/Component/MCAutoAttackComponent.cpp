// Copyright (c) 2024 tobenot, See LICENSE in the project root for license information.

// MC自动攻击组件实现文件 - MCAutoAttackComponent.cpp

#include "MCAutoAttackComponent.h"

#include "MCAttributeComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

UMCAutoAttackComponent::UMCAutoAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// 默认值
	AttackRange = 500.f; // 攻击范围，单位为厘米
	AttackInterval = 0.5f; // 攻击间隔，单位为秒
	Damage = 5.f;
	LastAttackTime = -AttackInterval; // 以便于游戏开始时就可以攻击

	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	DetectionSphere->InitSphereRadius(AttackRange);
	DetectionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DetectionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	DetectionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	DetectionSphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	DetectionSphere->SetHiddenInGame(false);
	DetectionSphere->ShapeColor = FColor::White;
}

void UMCAutoAttackComponent::BeginPlay()
{
	Super::BeginPlay();
}
void UMCAutoAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(GetOwner()->GetLocalRole() == ROLE_Authority) // 确保只有服务器执行以下逻辑
	{
		// 当前时间
		float CurrentTime = GetWorld()->GetTimeSeconds();

		// 检测是否是攻击时间
		if(CurrentTime - LastAttackTime >= AttackInterval)
		{
			CheckForEnemies();
		}
	}
}

void UMCAutoAttackComponent::PerformAttack(AActor* EnemyActor)
{
	// 获取敌人的属性组件
	UMCAttributeComponent* EnemyAttributeComp = Cast<UMCAttributeComponent>(EnemyActor->GetComponentByClass(UMCAttributeComponent::StaticClass()));
	if(EnemyAttributeComp)
	{
		// AddHealth负数来对敌人造成伤害
		EnemyAttributeComp->AddHealth(-Damage);
	}

	LastAttackTime = GetWorld()->GetTimeSeconds();
}

void UMCAutoAttackComponent::CheckForEnemies()
{
	TArray<AActor*> OverlappingActors;
	DetectionSphere->GetOverlappingActors(OverlappingActors);
	const UMCAttributeComponent* MyAttributeComp = Cast<UMCAttributeComponent>(GetOwner()->GetComponentByClass(UMCAttributeComponent::StaticClass()));
    
	if (MyAttributeComp)
	{
		if(MyAttributeComp->IsDead())
		{
			return;
		}
		float AttackDistance = DetectionSphere->GetScaledSphereRadius(); // Use the scaled sphere radius as the attack distance

		for (AActor* Actor : OverlappingActors)
		{
			const UMCAttributeComponent* AttributeComp = Cast<UMCAttributeComponent>(Actor->GetComponentByClass(UMCAttributeComponent::StaticClass()));
            
			if (AttributeComp &&
				((AttributeComp->GetFaction() == EMCFaction::Hostile && MyAttributeComp->GetFaction() == EMCFaction::Friendly)
				|| (AttributeComp->GetFaction() == EMCFaction::Friendly && MyAttributeComp->GetFaction() == EMCFaction::Hostile)))
			{
				// Check if the distance between the two actors is within the attack distance
				if (FVector::Dist(GetOwner()->GetActorLocation(), Actor->GetActorLocation()) <= AttackDistance)
				{
					PerformAttack(Actor);
					break; // Attack only one enemy at a time
				}
			}
		}
	}
}