// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "RunnerCharacter.generated.h"

class USphereComponent;
class UInteractionComponent;
class UScoreComponent;
class UWidgetComponent;
class UBehaviorTree;

USTRUCT(Blueprintable)
struct FRunnerInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Runner")
	FText RunnerName;
};

UCLASS()
class THETOY_API ARunnerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ARunnerCharacter();

	static FName InteractionComponentName;
	static FName ScoreComponentName;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Runner")
	TObjectPtr<USphereComponent> InteractionSphere;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Runner")
	TObjectPtr<UInteractionComponent> InteractionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Runner")
	TObjectPtr<UScoreComponent> ScoreComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Runner")
	TObjectPtr<UWidgetComponent> StateWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Runner|Behavior")
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Runner|Info", meta = (ShowOnlyInnerProperties))
	FRunnerInfo RunnerInfo;
	
	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Runner")
	void InitializeRunnerWidget();
};
