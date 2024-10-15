// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"
#include "TheToy/Input/PlayerInputConfig.h"

AHeroCharacter::AHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	FirstPersonHands = CreateDefaultSubobject<USkeletalMeshComponent>("CharacterMesh1");
	FirstPersonHands->SetOnlyOwnerSee(true);
	FirstPersonHands->SetupAttachment(GetRootComponent());
	FirstPersonHands->bCastDynamicShadow = false;
	FirstPersonHands->CastShadow = false;
}

void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(InputConfig);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InputConfig->MoveAction, ETriggerEvent::Triggered, this, &AHeroCharacter::InputMove);
		EnhancedInputComponent->BindAction(InputConfig->LookAction, ETriggerEvent::Triggered, this, &AHeroCharacter::InputLook);
		
		EnhancedInputComponent->BindAction(InputConfig->JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(InputConfig->JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
}

void AHeroCharacter::InputMove(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		FVector2D MovementVector = Value.Get<FVector2D>();
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AHeroCharacter::InputLook(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		FVector2D LookAxisVector = Value.Get<FVector2D>();
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

