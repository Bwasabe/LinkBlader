// Fill out your copyright notice in the Description page of Project Settings.


#include "LB_PlayerInteraction.h"

#include "EnhancedInputComponent.h"
#include "LB_Player.h"

void ULB_PlayerInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FHitResult HitResult;
	// LineTrace�??�고, Tag�?검?�해 ?�브?�트�??�으�?가?�옴
	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActor(m_Owner);

	const FVector start = m_Owner->GetActorLocation();
	m_ForwardPos = start + m_Owner->GetControlRotation().Vector() * m_InteractDistance;

	if(m_IsInteract) // ?�호?�용중이�??�재 Object�?ForwardPos�??�직인??
	{
		FHitResult LocationHit;
		
		FVector LerpPos = FMath::Lerp(m_InteractionComponent->GetComponentLocation(), m_ForwardPos, DeltaTime * 8);

		m_InteractionComponent->SetWorldLocation(LerpPos, true, &LocationHit, ETeleportType::TeleportPhysics);
		
		FRotator CurRot = m_InteractionComponent->GetComponentRotation();

		FRotator TargetRot = FRotator(0, m_Owner->GetActorRotation().Yaw + 90, 0);

		FRotator Rotator = FMath::RInterpTo(CurRot, TargetRot, DeltaTime, 10);

		m_InteractionComponent->SetWorldRotation(Rotator, true, nullptr, ETeleportType::TeleportPhysics);

		UE_LOG(LogTemp, Log, L"%s", *LocationHit.ImpactPoint.ToString() );
	}
	else // ?�호?�용중이 ?�니�?계속 ?�브?�트�?LineTrace�?찾고,
	{
		if(GetWorld()->LineTraceSingleByChannel(HitResult, start,m_ForwardPos,ECC_Visibility, collisionParams))
		{
			AActor* actor =HitResult.GetActor();
			if(!actor)return;
			
			if(actor->Tags.Num() > 0 && actor->Tags.Contains(L"Object"))
			{
				// UI켜주�?
				
				m_InteractionComponent = HitResult.GetComponent();
				return;
			}
		}
		m_InteractionComponent = nullptr;
	}
	
}

void ULB_PlayerInteraction::StartInteract(const FInputActionValue& InputActionValue)
{
	if(!m_InteractionComponent)return;
	
	const FVector Direction = m_ForwardPos - m_InteractionComponent->GetComponentLocation();

	m_InteractionComponent->SetEnableGravity(false);
	m_InteractionComponent->AddImpulse(Direction);
	
	m_IsInteract = true;
	
}

void ULB_PlayerInteraction::EndInteract(const FInputActionValue& InputActionValue)
{
	if(!m_InteractionComponent)return;

	m_InteractionComponent->SetEnableGravity(true);
	m_InteractionComponent->SetPhysicsLinearVelocity(FVector(0,0,0));
	
	m_InteractionComponent = nullptr;
	m_IsInteract = false;
}

void ULB_PlayerInteraction::BindAction(UEnhancedInputComponent* EnhancedInputComponent)
{
	EnhancedInputComponent->BindAction(m_InteractionAction, ETriggerEvent::Started, this, &ULB_PlayerInteraction::StartInteract);
	EnhancedInputComponent->BindAction(m_InteractionAction, ETriggerEvent::Completed, this, &ULB_PlayerInteraction::EndInteract);
}
