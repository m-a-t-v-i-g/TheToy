// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

UCLASS(ClassGroup = "The Toy", meta = (BlueprintSpawnableComponent))
class THETOY_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractionComponent();

	void SetupInteractionComponent(UShapeComponent* Shape);

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Interaction")
	TObjectPtr<UShapeComponent> Collision;
};
