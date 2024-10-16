// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteraction, AActor*, InteractedActor);

UCLASS(ClassGroup = "The Toy", meta = (BlueprintSpawnableComponent))
class THETOY_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractionComponent();

	UPROPERTY(BlueprintAssignable)
	FOnInteraction OnInteraction;
	
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
	
	void SetInteractionCollision(UShapeComponent* Shape);

	void SetupInteractionComponent();

protected:
	UPROPERTY(EditAnywhere, Category = "Interaction Component")
	TObjectPtr<UShapeComponent> Collision;

	UPROPERTY(EditAnywhere, Category = "Interaction Component")
	TSubclassOf<AActor> CheckActorsOfClass;

	UFUNCTION()
	void OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                             const FHitResult& SweepResult); 
};
