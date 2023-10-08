// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LB_Player.generated.h"

UCLASS()
class ALB_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALB_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION(BlueprintCallable, Category = "DeadFunc")
	void Dead();

private:
	void ReStartGame();
public:
	UPROPERTY(EditDefaultsOnly, Category = CameraShake)
	TSubclassOf<class UCameraShakeBase> m_CameraShakeClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* m_kMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* m_DieAction;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerComponent)
		class ULB_PlayerMovement* m_PlayerMovement;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerComponent)
		class ULB_PlayerInteraction* m_PlayerInteract;
		
private:
	FTimerHandle DelayedFunctionTimerHandle;

	bool m_IsDead;
};
