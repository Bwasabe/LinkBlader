// Fill out your copyright notice in the Description page of Project Settings.


#include "LB_PlayerInteraction.h"

#include "EnhancedInputComponent.h"
#include "LB_Player.h"
#include "Blueprint/UserWidget.h"


void ULB_PlayerInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FHitResult HitResult;
	// LineTrace를 쏘고, Tag를 검사해 오브젝트면 앞으로 가져옴
	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActor(m_Owner);

	const FVector Start = m_Owner->GetActorLocation();
	m_ForwardPos = Start + m_Owner->GetControlRotation().Vector() * m_InteractDistance;

	if(m_IsInteract) // 상호작용중이면 현재 Object를 ForwardPos로 움직인다
	{
		FHitResult LocationHit;
		
		FVector LerpPos = FMath::Lerp(m_InteractionComponent->GetComponentLocation(), m_ForwardPos, DeltaTime * 8);
		
		m_InteractionComponent->SetWorldLocation(LerpPos, true, &LocationHit, ETeleportType::TeleportPhysics);

		if(LocationHit.ImpactPoint != FVector::Zero() && FVector::Dist(LocationHit.ImpactPoint, Start) >= m_InteractDistance * 1.5f)
			m_InteractionComponent->SetWorldLocation(Start);

		FRotator CurRot = m_InteractionComponent->GetComponentRotation();
		FRotator TargetRot = FRotator(0, m_Owner->GetActorRotation().Yaw + 90, 0);
		FRotator Rotator = FMath::RInterpTo(CurRot, TargetRot, DeltaTime, 10);
		
		m_InteractionComponent->SetWorldRotation(Rotator, true, nullptr, ETeleportType::TeleportPhysics);
	}
	else // 상호작용중이 아니면 계속 오브젝트를 LineTrace로 찾고,
	{
		if(GetWorld()->LineTraceSingleByChannel(HitResult, Start,m_ForwardPos,ECC_Visibility, collisionParams))
		{
			AActor* actor =HitResult.GetActor();
			if(!actor)return;
			
			if(actor->Tags.Num() > 0 && actor->Tags.Contains(L"Object"))
			{

				InteractionWidget->SetVisibility(ESlateVisibility::Visible);
				
				m_InteractionComponent = HitResult.GetComponent();
				return;
			}
		}
		InteractionWidget->SetVisibility(ESlateVisibility::Hidden);
		m_InteractionComponent = nullptr;
	}
	
}

void ULB_PlayerInteraction::BeginPlay()
{
	Super::BeginPlay();

	if(InteractionWidgetClass != nullptr)
	{
		InteractionWidget = CreateWidget<UUserWidget>(GetWorld(), InteractionWidgetClass);
		if(InteractionWidget != nullptr)
		{
			InteractionWidget->AddToViewport();
			InteractionWidget->SetVisibility(ESlateVisibility::Hidden);
		}
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
