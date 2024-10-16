// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HeroToyComponent.generated.h"

class AToyActor;

UCLASS(ClassGroup = "The Toy", meta = (BlueprintSpawnableComponent))
class THETOY_API UHeroToyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHeroToyComponent();

	void ToggleToy();

	void LaunchToy();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Toy Component")
	TObjectPtr<UDataTable> ToysDataTable;

	UPROPERTY(EditInstanceOnly, Category = "Toy Component")
	TObjectPtr<AToyActor> CurrentToy;

private:
	UPROPERTY(EditInstanceOnly, Category = "Toy Component")
	bool bCanToggleToy = true;
};
