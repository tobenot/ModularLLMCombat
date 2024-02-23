// Copyright (c) 2024 tobenot, See LICENSE in the project root for license information.

// Inventory/MCInventoryComponent.cpp

#include "MCInventoryComponent.h"
#include "Net/UnrealNetwork.h"

UMCInventoryComponent::UMCInventoryComponent()
{
    // 设置此组件可以被复制
    SetIsReplicatedByDefault(true);
    AbilitySlots.Init(nullptr, MaxSlotLimit);
}

void UMCInventoryComponent::AddAbility(UMCAbilityBase* Ability)
{
    // 确保Ability不为空
    if (Ability)
    {
        Ability->BelongInventoryComponent = this;
        // 添加到背包能力列表
        Abilities.Add(Ability);

        // 尝试先放入空闲的物品栏
        for (int32 SlotIndex = 0; SlotIndex < MaxSlotLimit; ++SlotIndex)
        {
            // 如果当前栏位为空，则放入栏位
            if (AbilitySlots[SlotIndex] == nullptr)
            {
                AbilitySlots[SlotIndex] = Ability;
                break;
            }
        }
            
        // 如果是服务器，通知客户端更新
        if (GetOwnerRole() == ROLE_Authority)
        {
            // 更新客户端代码，可以根据实际需求来具体实现
            UE_LOG(LogTemp, Warning, TEXT("添加了能力：%s 到 %s的背包"), *Ability->GetName(),*GetOwner()->GetName());
        }
    }
}

TArray<UMCAbilityBase*> UMCInventoryComponent::GetAllAbility() const
{
    // 返回背包能力列表的复制
    return Abilities;
}

bool UMCInventoryComponent::TryUseAbilityFromSlot(int32 SlotIndex)
{
    UMCAbilityBase* Ability = GetAbilityFromSlot(SlotIndex);
    if (Ability)
    {
        ConsumeAbility(Ability);
        return true;  // 使用成功
    }
    return false;  // 栏位为空或指定的栏位无效
}

void UMCInventoryComponent::ConsumeAbility(UMCAbilityBase* Ability)
{
    // 确保Ability不为空且包含在背包中
    if (Ability && Abilities.Contains(Ability))
    {
        // 使用物品，具体逻辑可以根据物品具体功能实现
        Ability->Use();

        // 如果是消耗性物品，从列表中移除
        Abilities.RemoveSingle(Ability);

        // 如果是服务器，通知客户端更新
        if (GetOwnerRole() == ROLE_Authority)
        {
            // 更新客户端代码，可以根据实际需求来具体实现
        }
    }
}

void UMCInventoryComponent::SetAbilityToSlot(UMCAbilityBase* Ability, int32 SlotIndex)
{
    // 检查SlotIndex是否有效并且Ability不为空
    if (Ability && AbilitySlots.IsValidIndex(SlotIndex))
    {
        // 将能力设置到物品栏的相应位置
        AbilitySlots[SlotIndex] = Ability;

        // 如果是服务器，通知客户端更新
        if (GetOwnerRole() == ROLE_Authority)
        {
            // 更新客户端代码，可以根据实际需求来具体实现
        }
    }
}

UMCAbilityBase* UMCInventoryComponent::GetAbilityFromSlot(int32 SlotIndex) const
{
    // 检查SlotIndex是否有效
    if (AbilitySlots.IsValidIndex(SlotIndex))
    {
        // 返回指定位置的能力
        return AbilitySlots[SlotIndex];
    }

    // 如果无效则返回nullptr
    return nullptr;
}

void UMCInventoryComponent::RemoveAbility(UMCAbilityBase* Ability)
{
    if (!Ability) return;
    
    // 从背包能力列表中移除
    Abilities.RemoveSingle(Ability);
    // 从物品栏中移除
    for(int32 SlotIndex = 0; SlotIndex < AbilitySlots.Num(); SlotIndex++)
    {
        if(AbilitySlots[SlotIndex] == Ability)
        {
            AbilitySlots[SlotIndex] = nullptr;
            break; // 找到匹配项后退出循环
        }
    }
    
    // 如果是服务器，通知客户端更新
    if(GetOwnerRole() == ROLE_Authority)
    {
        // 更新客户端代码，这里可以根据实际需求来具体实现
        // 比如通过调用客户端的RPC函数来处理
        // ...
    }

    // 销毁物品对象
    Ability->ConditionalBeginDestroy();
}

// 用来告诉引擎如何复制这些属性
void UMCInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // 告诉引擎复制Abilities和AbilitySlots数组
    DOREPLIFETIME(UMCInventoryComponent, Abilities);
    DOREPLIFETIME(UMCInventoryComponent, AbilitySlots);
}
