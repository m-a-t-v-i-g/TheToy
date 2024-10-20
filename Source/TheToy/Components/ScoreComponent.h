// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreComponent.generated.h"

class AToyActor;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnScoreUpdated, class UScoreComponent*);

UCLASS(ClassGroup = "The Toy", meta = (BlueprintSpawnableComponent))
class THETOY_API UScoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UScoreComponent();

	FOnScoreUpdated OnScoreUpdated;
	
	void SetupScoreComponent();

	UFUNCTION(BlueprintCallable, Category = "Score Component")
	int GetScore() const { return Score; }
	
protected:
	UPROPERTY(EditInstanceOnly, Category = "Score Component")
	int Score = 0;

	UFUNCTION()
	void CheckToyInteraction(AActor* PossibleToy);

	void FetchToyInfo(const AToyActor* Toy);
};
