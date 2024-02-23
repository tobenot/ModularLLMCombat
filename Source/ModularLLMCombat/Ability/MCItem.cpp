// Copyright (c) 2024 tobenot, See LICENSE in the project root for license information.


#include "MCItem.h"
#include "Ability/MCInventoryComponent.h"

void UMCItem::Use_Implementation()
{
	// 假设调用Use表示使用了一个单位的物品
	if(Quantity > 0)
	{
		--Quantity;
        
		// 如果物品使用后数量为0，则从背包移除该物品
		if(Quantity == 0)
		{
			if(BelongInventoryComponent)
			{
				BelongInventoryComponent->RemoveAbility(this);
			}
		}
	}
}

bool UMCItem::Use_Validate()
{
	// 验证使用物品的条件，例如物品的数量是否大于0
	return Quantity > 0;
}