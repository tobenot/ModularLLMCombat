// Copyright (c) 2024 tobenot, See LICENSE in the project root for license information.
#include "MCAttributeComponent.h"
#include "Net/UnrealNetwork.h" // For DOREPLIFETIME()

// 设置默认属性值
UMCAttributeComponent::UMCAttributeComponent()
{
	// 设置默认健康值
	Health = 100.0f;
    
	// 默认为中立阵营
	Faction = EMCFaction::Neutral;
}

// 修改属性值
void UMCAttributeComponent::AddHealth(float Amount)
{
	if(GetOwnerRole() == ROLE_Authority)
	{
		Health += Amount;
		UE_LOG(LogTemp, Warning, TEXT("After - Owner: %s, Health: %f, Added: %f"), *GetOwner()->GetName(), Health, Amount);
	}
}

// 获取属性值
float UMCAttributeComponent::GetHealth() const
{
	return Health;
}

// 设置阵营
void UMCAttributeComponent::SetFaction(EMCFaction NewFaction)
{
	if(GetOwnerRole() == ROLE_Authority)
	{
		Faction = NewFaction;
	}
}

// 获取阵营
EMCFaction UMCAttributeComponent::GetFaction() const
{
	return Faction;
}

// 使用UNet来同步变量
void UMCAttributeComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMCAttributeComponent, Health);
	DOREPLIFETIME(UMCAttributeComponent, Faction);
}