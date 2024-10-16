// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "RunnerInterface.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Runner")
	float Speed = 0.0f;

	FRunnerInfo()
	{
		RunnerName = FText::FromString("Runner");
	}
};

UCLASS()
class THETOY_API ARunnerCharacter : public ABaseCharacter, public IRunnerInterface
{
	GENERATED_BODY()

public:
	ARunnerCharacter();

	static FName InteractionComponentName;
	static FName ScoreComponentName;

	virtual void OnRegistration(const FRunnerInfo& NewRunnerInfo) override;
	
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Runner")
	FRunnerInfo RunnerInfo;
	
	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Runner")
	void InitializeRunnerWidget();
};
