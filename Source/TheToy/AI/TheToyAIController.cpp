// Fill out your copyright notice in the Description page of Project Settings.

#include "TheToyAIController.h"

ATheToyAIController::ATheToyAIController()
{
}

void ATheToyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTreeAsset)
	{
		RunBehaviorTree(BehaviorTreeAsset);
	}
}
