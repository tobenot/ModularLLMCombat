// Copyright (c) 2024 tobenot, See LICENSE in the project root for license information.

#include "MCMonsterBase.h"
#include "Combat/Component/MCAttributeComponent.h"
#include "Combat/Component/MCAutoAttackComponent.h"

AMCMonsterBase::AMCMonsterBase()
{
	// 默认设置阵营为敌对
	Faction = EMCFaction::Hostile;
	AttributeComponent = CreateDefaultSubobject<UMCAttributeComponent>(TEXT("AttributeComponent"));
	AttributeComponent->SetFaction(Faction);
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