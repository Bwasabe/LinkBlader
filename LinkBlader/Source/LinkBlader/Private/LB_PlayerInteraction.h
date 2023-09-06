// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "LB_PlayerComponentBase.h"
#include "LB_PlayerInteraction.generated.h"

/**
 * 
 */
UCLASS()
class ULB_PlayerInteraction : public ULB_PlayerComponentBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* m_InteractionAction;

public:
	void Interact(const FInputActionValue& InputActionValue);
	virtual void BindAction(UEnhancedInputComponent* EnhancedInputComponent) override;
};
