// Copyright (c) 2024 tobenot, See LICENSE in the project root for license information.
#include "MCAttributeComponent.h"
#include "Net/UnrealNetwork.h" // For DOREPLIFETIME()

// 设置默认属性值
UMCAttributeComponent::UMCAttributeComponent()
{
	MaxHealth = 100.0f;
	// 设置默认健康值
	Health = MaxHealth;
	// 默认为中立阵营
	Faction = EMCFaction::Neutral;
}

void UMCAttributeComponent::AddHealth(float Amount)
{
	if(GetOwnerRole() == ROLE_Authority)
	{
		const float OldHealth = Health;
		Health += Amount;
		Health = FMath::Clamp(Health,0,99999999);
		
		// 调用血量变化多播
		if (!FMath::IsNearlyEqual(OldHealth, Health))
		{
			OnRep_Health();
		}

		// 检查角色是否死亡
		if (Health <= 0.0f && !bIsDead)
		{
			bIsDead = true;
			OnRep_IsDead();
		}
    
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
void UMCAttributeComponent::OnRep_Health()
{
	OnHealthChanged.Broadcast(this, Health, LastHealthRecorded ? Health-LastHealth: (LastHealthRecorded = true, Health-MaxHealth));
	LastHealth = Health;
}
void UMCAttributeComponent::OnRep_IsDead()
{
	if (bIsDead)
	{
		OnDeath.Broadcast(this);
	}
}

// 使用UNet来同步变量
void UMCAttributeComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMCAttributeComponent, Health);
	DOREPLIFETIME(UMCAttributeComponent, Faction);
	DOREPLIFETIME(UMCAttributeComponent, bIsDead);
}