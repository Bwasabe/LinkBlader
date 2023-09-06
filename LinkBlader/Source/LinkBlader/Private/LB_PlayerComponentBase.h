// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LB_PlayerComponentBase.generated.h"


UCLASS(Abstract)
class ULB_PlayerComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULB_PlayerComponentBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetOwner(class ALB_Player* owner);

	virtual void BindAction(UEnhancedInputComponent* EnhancedInputComponent){}
protected:
	class ALB_Player* m_Owner;
};
