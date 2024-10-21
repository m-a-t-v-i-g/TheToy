// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TheToyAIController.generated.h"

UCLASS(DisplayName = "The Toy AI Controller")
class THETOY_API ATheToyAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATheToyAIController();

	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Perception")
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset;
};
