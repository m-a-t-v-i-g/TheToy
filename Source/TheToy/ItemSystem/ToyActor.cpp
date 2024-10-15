// Fill out your copyright notice in the Description page of Project Settings.

#include "ToyActor.h"

AToyActor::AToyActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AToyActor::ActivateToy()
{
	OnActivated();
}

void AToyActor::OnActivated_Implementation()
{
	
}
