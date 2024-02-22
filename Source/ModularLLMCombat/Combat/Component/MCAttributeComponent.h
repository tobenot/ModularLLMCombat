// Copyright (c) 2024 tobenot, See LICENSE in the project root for license information.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MCAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealthChangedSignature, UMCAttributeComponent*, AttributeComp, float, NewHealth, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathSignature, UMCAttributeComponent*, AttributeComp);

/* 定义阵营的枚举 */
UENUM(BlueprintType)
enum class EMCFaction : uint8
{
	Friendly UMETA(DisplayName = "友方"),
	Neutral UMETA(DisplayName = "中立"),
	Hostile UMETA(DisplayName = "敌对")
};

/* MCAttributeComponent类声明 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MODULARLLMCOMBAT_API UMCAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:    
	// Sets default values for this component's properties
	UMCAttributeComponent();

public:
	/* 修改属性值的接口，增加或减少值amount */
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void AddHealth(float Amount);

	/* 获取属性值 */
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetHealth() const;

	/* 设置阵营 */
	UFUNCTION(BlueprintCallable, Category = "Faction")
	void SetFaction(EMCFaction NewFaction);

	/* 获取阵营 */
	UFUNCTION(BlueprintCallable, Category = "Faction")
	EMCFaction GetFaction() const;

	/* 血量变化多播 */
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChangedSignature OnHealthChanged;

	/* 死亡多播 */
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDeathSignature OnDeath;
	
	UFUNCTION(Blueprintable)
	bool IsDead() const{return bIsDead;}
	
protected:
	/* 角色的属性值 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_Health)
	float Health;
	
	/* 角色的属性值 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float MaxHealth;
	
	/* 角色的阵营 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
	EMCFaction Faction;

	/* 角色是否已死 */
	UPROPERTY(Transient, ReplicatedUsing = OnRep_IsDead)
	bool bIsDead;
	
	UFUNCTION()
	void OnRep_Health();
	
	/* 当bIsDead变化时调用来同步客户端状态 */
	UFUNCTION()
	void OnRep_IsDead();
	
	/* 网络复制：复制属性和阵营状态到客户端 */
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

private:
	float LastHealth;
	bool LastHealthRecorded = false;
};