// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToyActor.h"
#include "ItemSystemCore.generated.h"

USTRUCT()
struct FToysTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Item")
	TSubclassOf<AToyActor> ToyActorClass = AToyActor::StaticClass();
	
	UPROPERTY(EditAnywhere, Category = "Item")
	int Cost = 0;
};
