// Copyright (c) 2024 tobenot, See LICENSE in the project root for license information.

// MC自动攻击组件头文件 - MCAutoAttackComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "MCAutoAttackComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MODULARLLMCOMBAT_API UMCAutoAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:    
	// Sets default values for this component's properties
	UMCAutoAttackComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AutoAttack")
	USphereComponent* DetectionSphere;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:    
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* 攻击范围 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AutoAttack")
	float AttackRange;

	/* 攻击间隔时间 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AutoAttack")
	float AttackInterval;

	/* 上次攻击时间 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AutoAttack")
	float LastAttackTime;
	
	/* 攻击伤害 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AutoAttack")
	float Damage;
    
	/* 进行攻击的函数 */
	UFUNCTION(BlueprintCallable, Category = "AutoAttack")
	void PerformAttack(AActor* EnemyActor);

	/* 检查范围内的敌人 */
	UFUNCTION(BlueprintCallable, Category = "AutoAttack")
	void CheckForEnemies();

	bool bCloseToEnemy = false;
};