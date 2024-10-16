// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroToyComponent.h"

UHeroToyComponent::UHeroToyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UHeroToyComponent::ToggleToy()
{
	
}

void UHeroToyComponent::LaunchToy()
{
	
}
