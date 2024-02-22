// Copyright (c) 2024 tobenot, See LICENSE in the project root for license information.

// Ability/MCItem.h
#pragma once

#include "MCAbilityBase.h"
#include "MCItem.generated.h"

UCLASS()
class MODULARLLMCOMBAT_API UMCItem : public UMCAbilityBase
{
	GENERATED_BODY()

public:
	virtual void Use_Implementation() override;
	virtual bool Use_Validate() override;

	// 获取物品的数量
	UFUNCTION(BlueprintCallable, Category = "Item")
	int32 GetQuantity() const { return Quantity; }

	// 设置物品的数量
	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetQuantity(int32 NewQuantity) { Quantity = NewQuantity; }

protected:
	// 物品数量
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item", meta=(ClampMin="0"))
	int32 Quantity;
};