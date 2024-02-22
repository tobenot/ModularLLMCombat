// Copyright (c) 2024 tobenot, See LICENSE in the project root for license information.
// Ability/MCClearMonstersItem.h

#pragma once

#include "CoreMinimal.h"
#include "ModularLLMCombat/Ability/MCItem.h"
#include "MCItem_ClearMonsters.generated.h"

UCLASS()
class MODULARLLMCOMBAT_API UMCItem_ClearMonsters : public UMCItem
{
	GENERATED_BODY()
	
public:
	float ClearRadius = 1000.0f; // 清除半径单位范围的怪物
	
public:
	virtual void Use_Implementation() override;
	
protected:
	// 在服务端执行使用物品的逻辑
	void ClearMonster(FVector Location, float Radius);
};
