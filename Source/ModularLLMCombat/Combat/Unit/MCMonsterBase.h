// Copyright (c) 2024 tobenot, See LICENSE in the project root for license information.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MCMonsterBase.generated.h"

class UMCAutoAttackComponent;
enum class EMCFaction : uint8;
class UMCAttributeComponent;

UCLASS()
class MODULARLLMCOMBAT_API AMCMonsterBase : public AActor
{
	GENERATED_BODY()
 
public:    
	// Sets default values for this actor's properties
	AMCMonsterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 敌人的属性组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMCAttributeComponent* AttributeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMCAutoAttackComponent* AutoAttackComponent;
	
	// 敌人的阵营
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Faction")
	EMCFaction Faction;

public:    
	// 获取敌人的属性组件
	UFUNCTION(BlueprintCallable, Category = "Components")
	UMCAttributeComponent* GetAttributeComponent() const;
};