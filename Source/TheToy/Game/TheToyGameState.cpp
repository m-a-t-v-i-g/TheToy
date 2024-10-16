// Fill out your copyright notice in the Description page of Project Settings.

#include "TheToyGameState.h"
#include "RunnerCharacter.h"

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
	return NewRunnerInfo;
}
