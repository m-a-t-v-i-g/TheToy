// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreComponent.h"
#include "InteractionComponent.h"
#include "ItemSystem/ToyActor.h"

UScoreComponent::UScoreComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UScoreComponent::SetupScoreComponent()
{
	if (auto InteractionComponent = GetOwner()->GetComponentByClass<UInteractionComponent>())
	{
		InteractionComponent->OnInteraction.AddDynamic(this, &UScoreComponent::CheckToyInteraction);
	}
}

void UScoreComponent::CheckToyInteraction(AActor* PossibleToy)
{
	auto Toy = Cast<IToyInterface>(PossibleToy);
	if (!Toy) return;

	FetchToyInfo(Toy->GetToy());
	Toy->Grab();
}

void UScoreComponent::FetchToyInfo(const AToyActor* Toy)
{
	FToyHandle ToyInfo = Toy->GetToyInfo();
	Score += ToyInfo.Cost;
	OnScoreUpdated.Broadcast();
}
