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
	
	for (TActorIterator<AActor> It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (auto RunnerInterface = Cast<IRunnerInterface>(Actor))
		{
			FRunnerInfo RunnerInfo = ToyGameState->CreateInfoForRunner(
				RunnerConfig->RunnerNames, RunnerConfig->AvailableSpeeds, Actor);
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
