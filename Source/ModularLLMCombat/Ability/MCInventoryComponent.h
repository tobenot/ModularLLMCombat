// Copyright (c) 2024 tobenot, See LICENSE in the project root for license information.

// Inventory/MCInventoryComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MCAbilityBase.h"
#include "MCInventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MODULARLLMCOMBAT_API UMCInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
	
	UMCInventoryComponent();
	
public:    
	// 添加能力到背包
	UFUNCTION(BlueprintCallable, Category = "InventoryComponent")
	void AddAbility(UMCAbilityBase* Ability);

	// 从背包中获取能力
	UFUNCTION(BlueprintCallable, Category = "InventoryComponent")
	TArray<UMCAbilityBase*> GetAllAbility() const;

	UFUNCTION(BlueprintCallable, Category = "InventoryComponent")
	bool TryUseAbilityFromSlot(int32 SlotIndex);

	// 将能力放入指定的物品栏位置
	UFUNCTION(BlueprintCallable, Category = "InventoryComponent")
	void SetAbilityToSlot(UMCAbilityBase* Ability, int32 SlotIndex);

	// 获取指定物品栏位置的能力
	UFUNCTION(BlueprintCallable, Category = "InventoryComponent")
	UMCAbilityBase* GetAbilityFromSlot(int32 SlotIndex) const;

	// 消耗或者使用能力
	UFUNCTION(BlueprintCallable, Category = "InventoryComponent")
	void ConsumeAbility(UMCAbilityBase* Ability);
	
protected:
	// 能力列表
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InventoryComponent", Replicated)
	TArray<UMCAbilityBase*> Abilities;

	// 物品栏，也是能力的一个集合
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InventoryComponent", Replicated)
	TArray<UMCAbilityBase*> AbilitySlots;
	
	// 物品栏上限
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InventoryComponent", meta=(ClampMin="1"))
	int32 MaxSlotLimit = 10;
};
