// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheToyGameMode.h"
#include "EngineUtils.h"
#include "RunnerCharacter.h"
#include "RunnerConfig.h"
#include "RunnerInterface.h"
#include "TheToyGameInstance.h"
#include "TheToyGameState.h"

ATheToyGameMode::ATheToyGameMode()
{
}

void ATheToyGameMode::StartPlay()
{
	auto ToyGameState = GetGameState<ATheToyGameState>();
	if (!ToyGameState)
	{
		return;
	}
	
	auto GameInst = GetGameInstance<UTheToyGameInstance>();
	if (!GameInst)
	{
		return;
	}

	FTheToyGameRules GameRules = GameInst->GameRules;

	ToyGameState->GameTimerEndDelegate.AddDynamic(this, &ATheToyGameMode::OnGameEnd);
	ToyGameState->StartGameTimer(GameRules.GameTime);
	
	TArray<AActor*> Runners;
	
	for (TActorIterator<AActor> It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor->Implements<URunnerInterface>())
		{
			Runners.AddUnique(Actor);
		}
	}

	if (Runners.Num() > GameRules.Bots)
	{
		uint8 Difference = Runners.Num() - GameRules.Bots;
		
		for (uint8 i = 0; i < Difference; i++)
		{
			uint8 Index = FMath::RandRange(0, Runners.Num() - 1);
			Runners[Index]->Destroy();
			Runners.RemoveAt(Index);
		}
	}
	
	for (auto Runner : Runners)
	{
		if (auto RunnerInterface = Cast<IRunnerInterface>(Runner))
		{
			FRunnerInfo RunnerInfo = ToyGameState->CreateInfoForRunner(
				RunnerConfig->RunnerNames, RunnerConfig->AvailableSpeeds, Runner);
			RunnerInterface->OnRegistration(RunnerInfo);
		}
	}
	
	Super::StartPlay();
}

void ATheToyGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ATheToyGameMode::OnGameEnd(const FTheToyGameResult& GameResult)
{
	
}
