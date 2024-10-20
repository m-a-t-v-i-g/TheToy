// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheToyGameMode.generated.h"

struct FTheToyGameResult;
class URunnerConfig;

UCLASS(MinimalAPI)
class ATheToyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATheToyGameMode();

	virtual void StartPlay() override;

	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Runner")
	TObjectPtr<URunnerConfig> RunnerConfig;

	UFUNCTION()
	void OnGameEnd(const FTheToyGameResult& GameResult);
};



