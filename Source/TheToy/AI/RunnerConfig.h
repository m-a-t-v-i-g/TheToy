// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RunnerConfig.generated.h"

UCLASS()
class THETOY_API URunnerConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Info")
	TArray<FText> RunnerNames;
	
	UPROPERTY(EditAnywhere, Category = "Info")
	TArray<float> AvailableSpeeds;
};
