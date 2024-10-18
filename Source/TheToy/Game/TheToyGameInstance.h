// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TheToyGameInstance.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FTheToyGameRules
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rules")
	float GameTime = 180.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rules")
	int Bots = 5;

	void Clear()
	{
		GameTime = 180.0f;
		Bots = 5;
	}
};

UCLASS()
class THETOY_API UTheToyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FTheToyGameRules GameRules;

	UFUNCTION(BlueprintCallable, Category = "The Toy")
	void SaveServerSettings(const FTheToyGameRules& ServerSettings);
	
	void ClearServerSettings();
};
