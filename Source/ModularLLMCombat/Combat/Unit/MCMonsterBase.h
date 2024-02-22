// Copyright (c) 2024 tobenot, See LICENSE in the project root for license information.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MCMonsterBase.generated.h"

class USphereComponent;
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* CollisionComponent;
	
	// 敌人的阵营
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Faction")
	EMCFaction Faction;
public:    
	// 获取敌人的属性组件
	UFUNCTION(BlueprintCallable, Category = "Components")
	UMCAttributeComponent* GetAttributeComponent() const;

public:
	// 定义角色死亡的函数
	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OnMonsterDeath();

	// 一个处理角色死亡逻辑的函数
	UFUNCTION()
	void HandleDeath(UMCAttributeComponent* AttributeComp);
};