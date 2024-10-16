// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ToyInterface.generated.h"

class AToyActor;

UINTERFACE()
class UToyInterface : public UInterface
{
	GENERATED_BODY()
};

class THETOY_API IToyInterface
{
	GENERATED_BODY()

public:
	virtual void Grab();

	virtual AToyActor* GetToy();
};
