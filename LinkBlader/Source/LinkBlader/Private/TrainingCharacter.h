// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TrainingCharacter.generated.h"


UCLASS()
class ATrainingCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats");
	float maxHp; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats");
	float curHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats");
	float stunGauge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats");
	float attackPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats");
	float attackSpeed;

public:
	// Sets default values for this character's properties
	ATrainingCharacter();  

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	void AddComp(ModuleType _moduleType, class UEnemyBaseComponent* _newComp);
	
	template<typename T> 
	T* GetComp(ModuleType _moduleType);
protected:
	TMap< ModuleType, class UEnemyBaseComponent*> compMap;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = EnemyComponent)
		class UEnemyAttackComp* enemyAttackComp;
};
UENUM(BlueprintType)
enum class ModuleType : uint8
{
	Move UMETA(DisplayName = "Move"),
	Attack UMETA(DisplayName = "Attack"),
};	