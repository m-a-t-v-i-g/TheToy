// Fill out your copyright notice in the Description page of Project Settings.

#include "TheToyAIController.h"
#include "Perception/AIPerceptionComponent.h"

ATheToyAIController::ATheToyAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATheToyAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
