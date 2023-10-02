// Fill out your copyright notice in the Description page of Project Settings.


#include "LB_PhysicsObjectBase.h"

// Sets default values
ALB_PhysicsObjectBase::ALB_PhysicsObjectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALB_PhysicsObjectBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALB_PhysicsObjectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

