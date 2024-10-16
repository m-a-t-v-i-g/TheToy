// Fill out your copyright notice in the Description page of Project Settings.

#include "RunnerCharacter.h"
#include "InteractionComponent.h"
#include "ScoreComponent.h"
#include "TheToyAIController.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

FName ARunnerCharacter::InteractionComponentName {"InteractionComp"};
FName ARunnerCharacter::ScoreComponentName {"ScoreComponent"};

ARunnerCharacter::ARunnerCharacter()
{
	InteractionSphere = CreateDefaultSubobject<USphereComponent>("InteractionSphere");
	InteractionSphere->SetupAttachment(GetRootComponent());
	
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(InteractionComponentName);
	InteractionComponent->SetInteractionCollision(InteractionSphere);

	ScoreComponent = CreateDefaultSubobject<UScoreComponent>(ScoreComponentName);
	
	StateWidget = CreateDefaultSubobject<UWidgetComponent>("State Widget");
	StateWidget->SetupAttachment(GetRootComponent());
	
	AIControllerClass = ATheToyAIController::StaticClass();
}

void ARunnerCharacter::OnRegistration(const FRunnerInfo& NewRunnerInfo)
{
	RunnerInfo = NewRunnerInfo;
	GetCharacterMovement()->MaxWalkSpeed = NewRunnerInfo.Speed;
}

void ARunnerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ScoreComponent)
	{
		ScoreComponent->SetupScoreComponent();
	}

	if (InteractionComponent)
	{
		InteractionComponent->SetupInteractionComponent();
	}
}

void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (StateWidget)
	{
		InitializeRunnerWidget();
	}
}

void ARunnerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, RunnerInfo);
}
