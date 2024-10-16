// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RunnerCharacter.h"
#include "GameFramework/GameStateBase.h"
#include "TheToyGameState.generated.h"

class ARunnerCharacter;

UCLASS()
class THETOY_API ATheToyGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	FRunnerInfo CreateInfoForRunner(const TArray<FText>& Names, const TArray<float>& Speeds, AActor* Runner);

private:
	TArray<FString> UnavailableNames;
};
