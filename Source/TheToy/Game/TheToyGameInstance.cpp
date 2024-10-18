// Fill out your copyright notice in the Description page of Project Settings.

#include "TheToyGameInstance.h"

void UTheToyGameInstance::SaveServerSettings(const FTheToyGameRules& ServerSettings)
{
	GameRules = ServerSettings;
}

void UTheToyGameInstance::ClearServerSettings()
{
	GameRules.Clear();
}
