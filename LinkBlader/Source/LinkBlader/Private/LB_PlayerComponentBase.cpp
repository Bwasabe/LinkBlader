// Fill out your copyright notice in the Description page of Project Settings.


#include "LB_PlayerComponentBase.h"

#include "LB_Player.h"

// Sets default values for this component's properties
ULB_PlayerComponentBase::ULB_PlayerComponentBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULB_PlayerComponentBase::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ULB_PlayerComponentBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULB_PlayerComponentBase::SetOwner(ALB_Player* owner)
{
	m_Owner = owner;
}

