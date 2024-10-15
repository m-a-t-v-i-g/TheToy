// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "RunnerCharacter.generated.h"

class UBehaviorTree;
class USphereComponent;
class UInteractionComponent;

UCLASS()
class THETOY_API ARunnerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ARunnerCharacter();

	static FName InteractionComponentName;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Runner")
	TObjectPtr<USphereComponent> InteractionSphere;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Runner")
	TObjectPtr<UInteractionComponent> InteractionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Runner|Behavior")
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset;
};
