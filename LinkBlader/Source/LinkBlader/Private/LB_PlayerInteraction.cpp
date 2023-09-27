// Fill out your copyright notice in the Description page of Project Settings.


#include "LB_PlayerInteraction.h"

#include "EnhancedInputComponent.h"
#include "LB_Player.h"

void ULB_PlayerInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FHitResult HitResult;
	// LineTrace를 쏘고, Tag를 검사해 오브젝트면 앞으로 가져옴
	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActor(m_Owner);

	const FVector start = m_Owner->GetActorLocation();
	m_ForwardPos = start + m_Owner->GetControlRotation().Vector() * m_InteractDistance;

	if(m_IsInteract) // 상호작용중이면 현재 Object를 ForwardPos로 움직인다
	{
		// FVector lerpPos = FMath::Lerp(m_CurrentInteractionObject->GetActorLocation(), m_ForwardPos, GetWorld()->DeltaTimeSeconds * m_LerpSmooth);

		// m_CurrentInteractionObject->SetActorLocation(lerpPos, true);

		FVector Direction = m_ForwardPos - m_InteractionComponent->GetComponentLocation();
		
		m_InteractionComponent->SetPhysicsLinearVelocity(Direction * m_MovePower);

		UE_LOG(LogTemp, Log, TEXT("%s"), *Direction.ToString() );
	}
	else // 상호작용중이 아니면 계속 오브젝트를 LineTrace로 찾고,
	{
		if(GetWorld()->LineTraceSingleByChannel(HitResult, start,m_ForwardPos,ECC_Visibility, collisionParams))
		{
			if(HitResult.GetActor()->Tags.Num() > 0 && HitResult.GetActor()->Tags.Contains(L"Object"))
			{
				UE_LOG(LogTemp, Log, L"Hit");
				// UI켜주기

				m_CurrentInteractionObject = HitResult.GetActor();
				m_InteractionComponent = HitResult.GetComponent();
				return;
			}
		}
		m_CurrentInteractionObject = nullptr;
	}
	
}

void ULB_PlayerInteraction::StartInteract(const FInputActionValue& InputActionValue)
{
	if(!m_CurrentInteractionObject)return;
	
	FVector Direction = m_ForwardPos - m_InteractionComponent->GetComponentLocation();

	m_InteractionComponent->SetEnableGravity(false);
	m_InteractionComponent->AddImpulse(Direction);
	
	m_IsInteract = true;
	
}

void ULB_PlayerInteraction::EndInteract(const FInputActionValue& InputActionValue)
{
	m_InteractionComponent->SetEnableGravity(true);
	m_InteractionComponent->SetPhysicsLinearVelocity(FVector(0,0,0));

	m_InteractionComponent = nullptr;
	m_IsInteract = false;
	m_CurrentInteractionObject = nullptr;
}

void ULB_PlayerInteraction::BindAction(UEnhancedInputComponent* EnhancedInputComponent)
{
	EnhancedInputComponent->BindAction(m_InteractionAction, ETriggerEvent::Started, this, &ULB_PlayerInteraction::StartInteract);
	EnhancedInputComponent->BindAction(m_InteractionAction, ETriggerEvent::Completed, this, &ULB_PlayerInteraction::EndInteract);

}
