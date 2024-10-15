// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionComponent.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractionComponent::SetupInteractionComponent(UShapeComponent* Shape)
{
	if (Shape)
	{
		Collision = Shape;
	}
}
