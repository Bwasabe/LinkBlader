// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainingCharacter.h"
#include "EnemyAttackComp.h"

// Sets default values
ATrainingCharacter::ATrainingCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	enemyAttackComp = CreateDefaultSubobject<UEnemyAttackComp>(L"EnemyAttackComp");
}

// Called when the game starts or when spawned
void ATrainingCharacter::BeginPlay()
{
	Super::BeginPlay();
	AddComp(ModuleType::Attack, enemyAttackComp);
}

// Called every frame
void ATrainingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrainingCharacter::AddComp(ModuleType _moduleType, UEnemyBaseComponent* _newComp)
{
	if (compMap.Contains(_moduleType) == false)
	{
		compMap.Add(_moduleType, _newComp);
	}
}

template<typename T>
T* ATrainingCharacter::GetComp(ModuleType _moduleType)
{
	T* _findModule = nullptr; 
	if (compMap.Contains(_moduleType) == true)
	{
		_findModule = compMap.Find(_moduleType);
	}
	return _findModule; 
}


FString EnumToString(ModuleType EnumValue)
{
    UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ModuleType"), true);

    if (!EnumPtr)
    {
        return FString("Invalid");
    }

    return EnumPtr->GetNameStringByIndex(static_cast<int32>(EnumValue));
}
