// Copyright (c) 2024 tobenot, See LICENSE in the project root for license information.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MCAbilityBase.generated.h"

class UMCInventoryComponent;
/**
 * 
 */
UCLASS()
class MODULARLLMCOMBAT_API UMCAbilityBase : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(Server, Reliable, WithValidation)
	virtual void Use();
public:
	FString GetAbilityName() const;
	void SetAbilityName(const FString& AbilityName);

public:
	UPROPERTY()
	UMCInventoryComponent* BelongInventoryComponent;

private:
	FString AbilityName;
};
