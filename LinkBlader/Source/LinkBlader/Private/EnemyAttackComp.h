// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBaseComponent.h"
#include "EnemyAttackComp.generated.h"

/**
 * 
 */
UCLASS()
class UEnemyAttackComp : public UEnemyBaseComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		void MeleeAttack();		
};
