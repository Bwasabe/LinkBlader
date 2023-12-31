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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Interact )
	float m_InteractDistance = 300;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Interact )
	float m_MovePower = 4.f;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
public:
	UPrimitiveComponent* m_InteractionComponent;

	bool m_IsInteract;

	FVector m_ForwardPos;
public:
	void StartInteract(const FInputActionValue& InputActionValue);
	void EndInteract(const FInputActionValue& InputActionValue);
	virtual void BindAction(UEnhancedInputComponent* EnhancedInputComponent) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = Widget)
		TSubclassOf<class UUserWidget> InteractionWidgetClass;
private:
	UUserWidget* InteractionWidget;
};
