// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HeroToyComponent.generated.h"

UCLASS(ClassGroup = "The Toy", meta = (BlueprintSpawnableComponent))
class THETOY_API UHeroToyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHeroToyComponent();

protected:
	
};
