// Fill out your copyright notice in the Description page of Project Settings.


#include "LB_Player.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "LB_PlayerComponentBase.h"
#include "LB_PlayerInteraction.h"
#include "LB_PlayerMovement.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALB_Player::ALB_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_PlayerMovement = CreateDefaultSubobject<ULB_PlayerMovement>(L"PlayerMovement");
	m_PlayerInteract = CreateDefaultSubobject<ULB_PlayerInteraction>(L"PlayerInteraction");
}

// Called when the game starts or when spawned
void ALB_Player::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALB_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALB_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UE_LOG(LogTemp, Log, L"BindAction");
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(m_kMappingContext, 0);
		}
	}
	

	UEnhancedInputComponent* EnhancedInputComp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	if (!EnhancedInputComp)return;


	TInlineComponentArray<ULB_PlayerComponentBase*> components;

	GetComponents(components);
	for(auto* component : components)
	{
		component->SetOwner(this);
		component->BindAction(EnhancedInputComp);
	}

	EnhancedInputComp->BindAction(m_DieAction, ETriggerEvent::Triggered, this, &ALB_Player::Dead);

}

void ALB_Player::Dead()
{
	m_PlayerMovement->CantMove = true;
	m_PlayerMovement->CantTurn = true;

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();; 
	if (PlayerController)
		PlayerController->PlayerCameraManager->StartCameraShake(m_CameraShakeClass);

	float DelaySeconds = 0.8f;
        
        // Set a timer to call YourDelayedFunction after the specified delay.
        GetWorldTimerManager().SetTimer(DelayedFunctionTimerHandle, this, &ALB_Player::Restart, DelaySeconds, false);
}

void ALB_Player::Restart()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	
	UGameplayStatics::OpenLevel(this, *CurrentLevelName, true);
}


