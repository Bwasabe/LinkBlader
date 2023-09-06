// Fill out your copyright notice in the Description page of Project Settings.


#include "LB_PlayerInteraction.h"

#include "EnhancedInputComponent.h"

void ULB_PlayerInteraction::Interact(const FInputActionValue& InputActionValue)
{
	
}

void ULB_PlayerInteraction::BindAction(UEnhancedInputComponent* EnhancedInputComponent)
{
	EnhancedInputComponent->BindAction(m_InteractionAction, ETriggerEvent::Triggered, this, &ULB_PlayerInteraction::Interact);
}
