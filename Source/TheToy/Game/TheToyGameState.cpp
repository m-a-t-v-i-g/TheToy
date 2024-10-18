// Fill out your copyright notice in the Description page of Project Settings.

#include "TheToyGameState.h"
#include "RunnerCharacter.h"
#include "ScoreComponent.h"
#include "Net/UnrealNetwork.h"

ATheToyGameState::ATheToyGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATheToyGameState::StartGameTimer(float GameTime)
{
	GetWorldTimerManager().SetTimer(GameTimer, this, &ATheToyGameState::OnGameTimerEnd, GameTime, false);
}

void ATheToyGameState::OnGameTimerEnd()
{
	FTheToyGameResult GameResult;
	FText RunnerName;
	float MaxScore = 0;
	bool bDrawnGame = false;
	
	for (auto& Statistics : RunnerStatistics)
	{
		if (Statistics.Score == MaxScore)
		{
			RunnerName = FText::FromString("");
			MaxScore = 0;
			bDrawnGame = true;
		}
		if (Statistics.Score > MaxScore)
		{
			RunnerName = Statistics.RunnerName;
			MaxScore = Statistics.Score;
			bDrawnGame = false;
		}
	}

	GameResult.WinnerName = RunnerName;
	GameResult.WinnerScore = MaxScore;
	GameResult.bDrawnGame = bDrawnGame;
	
	MulticastGameTimerEnd(GameResult);
}

void ATheToyGameState::MulticastGameTimerEnd_Implementation(const FTheToyGameResult& GameResult)
{
	GameTimerEndDelegate.Broadcast(GameResult);
}

FRunnerInfo ATheToyGameState::CreateInfoForRunner(const TArray<FText>& Names, const TArray<float>& Speeds, AActor* Runner)
{
	TArray<FString> AvailableNames;
	for (auto RunnerName : Names)
	{
		FString StringName = RunnerName.ToString();
		if (!UnavailableNames.Contains(StringName))
		{
			AvailableNames.AddUnique(StringName);
		}
	}

	FRunnerInfo NewRunnerInfo;
	NewRunnerInfo.Speed = Speeds[FMath::RandRange(0, Speeds.Num() - 1)];
	
	if (!AvailableNames.IsEmpty())
	{
		FString StringName = AvailableNames[FMath::RandRange(0, AvailableNames.Num() - 1)];
		
		NewRunnerInfo.RunnerName = FText::FromString(StringName);
		UnavailableNames.AddUnique(StringName);
	}

	if (auto ScoreComp = Runner->GetComponentByClass<UScoreComponent>())
	{
		ScoreComp->OnScoreUpdated.AddUObject(this, &ATheToyGameState::UpdateRunnerStatistics);
	}
	
	return NewRunnerInfo;
}

void ATheToyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, RunnerStatistics);
	DOREPLIFETIME(ThisClass, TimeRemaining);
}

void ATheToyGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (HasAuthority())
	{
		TimeRemaining = GetWorldTimerManager().GetTimerRemaining(GameTimer);
	}
}

void ATheToyGameState::UpdateRunnerStatistics()
{
	
}
