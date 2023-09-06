// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LB_PlayerComponentBase.h"
#include "EnhancedInputComponent.h"
#include "LB_PlayerMovement.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ULB_PlayerMovement : public ULB_PlayerComponentBase
{
	GENERATED_BODY()

	
private:
	FVector2D m_MoveDir;


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* m_MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* m_JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* m_TurnAction;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BindAction(UEnhancedInputComponent* EnhancedInputComponent) override;

	virtual void BeginPlay() override;

	// void MovingForward();
	// void OnWall();
	// void ConsumeJump();

	void Move(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);

};
