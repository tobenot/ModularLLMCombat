// Copyright (c) 2024 tobenot, See LICENSE in the project root for license information.


#include "MCItem.h"

void UMCItem::Use_Implementation()
{
	// 物品使用的逻辑代码
	--Quantity;
}

bool UMCItem::Use_Validate()
{
	// 验证使用物品的条件，例如物品的数量是否大于0
	return Quantity > 0;
}