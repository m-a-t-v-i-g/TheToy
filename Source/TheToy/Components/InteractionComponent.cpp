// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionComponent.h"
#include "Components/ShapeComponent.h"

UInteractionComponent::UInteractionComponent()
{
	bWantsInitializeComponent = true;
	
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractionComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);

	Collision->OnComponentBeginOverlap.RemoveAll(this);
}

void UInteractionComponent::SetInteractionCollision(UShapeComponent* Shape)
{
	if (!Shape || Shape == Collision) return;
	
	Collision = Shape;
}

void UInteractionComponent::SetupInteractionComponent()
{
	if (IsValid(Collision))
	{
		Collision->OnComponentBeginOverlap.AddDynamic(this, &UInteractionComponent::OnCollisionBeginOverlap);
	}
}

void UInteractionComponent::OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                                    AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                                    int32 OtherBodyIndex,
                                                    bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetOwner()->HasAuthority())
	{
		if (OtherActor->IsA(CheckActorsOfClass))
		{
			OnInteraction.Broadcast(OtherActor);
		}
	}
}
