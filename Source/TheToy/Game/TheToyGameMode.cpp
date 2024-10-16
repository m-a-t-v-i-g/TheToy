// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheToyGameMode.h"
#include "EngineUtils.h"
#include "RunnerCharacter.h"
#include "RunnerConfig.h"
#include "RunnerInterface.h"
#include "TheToyGameState.h"

ATheToyGameMode::ATheToyGameMode()
{
}

void ATheToyGameMode::StartPlay()
{
	if (auto ToyGameState = GetGameState<ATheToyGameState>())
	{
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
	}
	Super::StartPlay();
}
