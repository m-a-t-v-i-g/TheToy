// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroCharacter.h"
#include "EnhancedInputComponent.h"
#include "HeroToyComponent.h"
#include "InputActionValue.h"
#include "PlayerInputConfig.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "ItemSystem/ItemSystemCore.h"

FName AHeroCharacter::ToyComponentName {"ToyComponent"};

AHeroCharacter::AHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	CameraComponent->bUsePawnControlRotation = true;

	ToyMesh1P = CreateDefaultSubobject<UStaticMeshComponent>("ToyMesh1P");
	ToyMesh1P->SetupAttachment(CameraComponent);

	ToyMesh3P = CreateDefaultSubobject<UStaticMeshComponent>("ToyMesh3P");
	ToyMesh3P->SetupAttachment(GetMesh(), "ToySocket");

	ToyComponent = CreateDefaultSubobject<UHeroToyComponent>(ToyComponentName);
}

void AHeroCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ToyComponent)
	{
		ToyComponent->OnToyChanged.AddUObject(this, &AHeroCharacter::OnToyChanged);
		ToyComponent->OnToyLaunched.AddUObject(this, &AHeroCharacter::OnToyLaunched);
		ToyComponent->OnToyGrabbed.AddUObject(this, &AHeroCharacter::OnToyGrabbed);
		ToyComponent->SetupToyComponent();
	}
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

		EnhancedInputComponent->BindAction(InputConfig->ShootAction, ETriggerEvent::Started, this, &AHeroCharacter::InputShoot);
		EnhancedInputComponent->BindAction(InputConfig->ToggleToyAction, ETriggerEvent::Completed, this, &AHeroCharacter::InputToggleToy);
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

void AHeroCharacter::InputShoot(const FInputActionValue& Value)
{
	if (ToyComponent)
	{
		ToyComponent->LaunchToy();
	}
}

void AHeroCharacter::InputToggleToy(const FInputActionValue& Value)
{
	if (ToyComponent)
	{
		ToyComponent->ToggleToy();
	}
}

void AHeroCharacter::DrawToy(const FToyHandle& ToyHandle)
{
	if (ToyComponent)
	{
		auto ToysDT = ToyComponent->ToysDataTable;
		check(ToysDT);

		if (auto Row = ToysDT->FindRow<FToysTableRow>(ToyHandle.RowName, ""))
		{
			ToyMesh1P->SetStaticMesh(Row->PreviewMesh);
			ToyMesh3P->SetStaticMesh(Row->PreviewMesh);
		}
	}
}

void AHeroCharacter::OnToyChanged(const FToyHandle& ToyHandle)
{
	check(ToyComponent);
	
	DrawToy(ToyHandle);
}

void AHeroCharacter::OnToyLaunched()
{
	check(ToyMesh1P && ToyMesh3P);
	
	ToyMesh1P->SetStaticMesh(nullptr);
	ToyMesh3P->SetStaticMesh(nullptr);
}

void AHeroCharacter::OnToyGrabbed()
{
	check(ToyComponent);

	DrawToy(ToyComponent->GetCurrentToyHandle());
}
