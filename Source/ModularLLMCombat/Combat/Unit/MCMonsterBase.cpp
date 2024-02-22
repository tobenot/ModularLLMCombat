// Copyright (c) 2024 tobenot, See LICENSE in the project root for license information.

#include "MCMonsterBase.h"
#include "Combat/Component/MCAttributeComponent.h"
#include "Combat/Component/MCAutoAttackComponent.h"

AMCMonsterBase::AMCMonsterBase()
{
	// 初始化碰撞组件，并将其附加到根组件
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetCollisionProfileName(TEXT("WorldDynamic")); // 设置为世界动态的碰撞预设
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->CanCharacterStepUpOn = ECB_No;
	SetRootComponent(CollisionComponent);
	
	// 默认设置阵营为敌对
	Faction = EMCFaction::Hostile;
	AttributeComponent = CreateDefaultSubobject<UMCAttributeComponent>(TEXT("AttributeComponent"));
	if(AttributeComponent)
	{
		AttributeComponent->SetFaction(Faction);
		AttributeComponent->OnDeath.AddDynamic(this, &AMCMonsterBase::HandleDeath);
	}
	AutoAttackComponent = CreateDefaultSubobject<UMCAutoAttackComponent>(TEXT("AutoAttackComponent"));
	AutoAttackComponent->DetectionSphere->SetupAttachment(GetRootComponent());
}

void AMCMonsterBase::BeginPlay()
{
	Super::BeginPlay();

}

UMCAttributeComponent* AMCMonsterBase::GetAttributeComponent() const
{
	return AttributeComponent;
}

void AMCMonsterBase::HandleDeath(UMCAttributeComponent* AttributeComp)
{
	// 将角色放倒，这里将Roll轴旋转至-90度
	FRotator DeathRotation = GetActorRotation();
	DeathRotation.Roll = -90.0f;
	SetActorRotation(DeathRotation);

	// 调用蓝图实现的事件，可以用于触发UI等
	OnMonsterDeath();
}