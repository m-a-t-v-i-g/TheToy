// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RunnerCharacter.h"
#include "GameFramework/GameStateBase.h"
#include "TheToyGameState.generated.h"

class ARunnerCharacter;

USTRUCT(Blueprintable, BlueprintType)
struct FRunnerStatisticHandle
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Statistics")
	FText RunnerName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Statistics")
	int Score = 0;
};

USTRUCT(Blueprintable, BlueprintType)
struct FTheToyGameResult
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Result")
	FText WinnerName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Result")
	int WinnerScore = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Result")
	bool bDrawnGame = false;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameTimerEndDelegate, const FTheToyGameResult&, GameResult);

UCLASS()
class THETOY_API ATheToyGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ATheToyGameState();
	
	UPROPERTY(BlueprintAssignable)
	FOnGameTimerEndDelegate GameTimerEndDelegate;
	
	void StartGameTimer(float GameTime);

	void OnGameTimerEnd();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastGameTimerEnd(const FTheToyGameResult& GameResult);
	
	FRunnerInfo CreateInfoForRunner(const TArray<FText>& Names, const TArray<float>& Speeds, AActor* Runner);

	UFUNCTION(BlueprintCallable, Category = "Game")
	float GetRemainingTimeToEnd() const { return TimeRemaining; }
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Tick(float DeltaSeconds) override;
	
	void UpdateRunnerStatistics();
	
private:
	UPROPERTY(EditInstanceOnly, Replicated, Category = "Statistics")
	TArray<FRunnerStatisticHandle> RunnerStatistics;

	UPROPERTY(Replicated)
	float TimeRemaining = 0.0f;
	
	TArray<FString> UnavailableNames;

	FTimerHandle GameTimer;
};
