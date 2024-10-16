// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RunnerInterface.generated.h"

struct FRunnerInfo;

UINTERFACE()
class URunnerInterface : public UInterface
{
	GENERATED_BODY()
};

class THETOY_API IRunnerInterface
{
	GENERATED_BODY()

public:
	virtual void OnRegistration(const FRunnerInfo& NewRunnerInfo);
};
