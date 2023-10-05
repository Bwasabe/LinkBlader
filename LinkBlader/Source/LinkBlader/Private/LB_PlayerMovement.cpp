// Fill out your copyright notice in the Description page of Project Settings.


#include "LB_PlayerMovement.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "LB_Player.h"
#include "GameFramework/CharacterMovementComponent.h"


void ULB_PlayerMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULB_PlayerMovement::BindAction(UEnhancedInputComponent* EnhancedInputComponent)
{
	Super::BindAction(EnhancedInputComponent);
	// Move
	EnhancedInputComponent->BindAction(m_MoveAction, ETriggerEvent::Triggered, this, &ULB_PlayerMovement::Move);

	// Jump
	EnhancedInputComponent->BindAction(m_JumpAction, ETriggerEvent::Triggered, this, &ULB_PlayerMovement::Jump);
	EnhancedInputComponent->BindAction(m_JumpAction, ETriggerEvent::Completed, m_Owner, &ACharacter::StopJumping);

	//Turn
	EnhancedInputComponent->BindAction(m_TurnAction, ETriggerEvent::Triggered, this, &ULB_PlayerMovement::Turn);
}

void ULB_PlayerMovement::BeginPlay()
{
	Super::BeginPlay();

	// m_Owner -> LandedDelegate.Add()
}


void ULB_PlayerMovement::Jump(const FInputActionValue& Value)
{
	if(CantMove)return;
	m_Owner->Jump();
}

void ULB_PlayerMovement::Move(const FInputActionValue& Value)
{
	if(CantMove)return;
	
	m_MoveDir = Value.Get<FVector2D>();

	if(m_Owner->Controller != nullptr)
	{
		
		const FRotator rotation = m_Owner->Controller->GetControlRotation();
		
		const FRotator yawRotation(0, rotation.Yaw, 0);

		const FRotationMatrix matrix = FRotationMatrix(yawRotation); 
		
		const FVector forwardDir = matrix.GetUnitAxis(EAxis::X);
		const FVector rightDir = matrix.GetUnitAxis(EAxis::Y);

		m_MoveDir.Normalize();

		m_Owner->AddMovementInput(forwardDir, m_MoveDir.Y);
		m_Owner->AddMovementInput(rightDir, m_MoveDir.X);

	}
}

void ULB_PlayerMovement::Turn(const FInputActionValue& Value)
{
	if(CantTurn)return;
	
	FVector2D turn = Value.Get<FVector2D>();
	if(m_Owner->Controller != nullptr)
	{
		m_Owner->AddControllerYawInput(turn.X);
		m_Owner->AddControllerPitchInput(-turn.Y);
	}
}
