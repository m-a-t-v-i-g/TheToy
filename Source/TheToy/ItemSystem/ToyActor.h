// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ToyActor.generated.h"

UCLASS()
class THETOY_API AToyActor : public AActor
{
	GENERATED_BODY()

public:
	AToyActor();

	void ActivateToy();

	UFUNCTION(BlueprintNativeEvent, Category = "Toy")
	void OnActivated();
	
protected:

private:
	bool bActive = false;
};
