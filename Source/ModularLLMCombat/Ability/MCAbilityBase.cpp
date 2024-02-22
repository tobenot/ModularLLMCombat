// Copyright (c) 2024 tobenot, See LICENSE in the project root for license information.


#include "MCAbilityBase.h"

void UMCAbilityBase::Use_Implementation()
{
}

bool UMCAbilityBase::Use_Validate()
{
	return true;
}

FString UMCAbilityBase::GetAbilityName() const
{
	return AbilityName;
}

void UMCAbilityBase::SetAbilityName(const FString& Name)
{
	AbilityName = Name;
}
