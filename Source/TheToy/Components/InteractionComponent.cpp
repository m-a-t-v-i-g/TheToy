// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionComponent.h"
#include "Components/ShapeComponent.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractionComponent::SetInteractionCollision(UShapeComponent* Shape)
{
	if (Shape == Collision) return;
	
	if (Shape)
	{
		Collision = Shape;
	}
}
