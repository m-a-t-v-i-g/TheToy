// Fill out your copyright notice in the Description page of Project Settings.

#include "ToyActor.h"
#include "Components/SphereComponent.h"

AToyActor::AToyActor()
{
	PhysicCollision = CreateDefaultSubobject<USphereComponent>("Physic Collision");
	SetRootComponent(PhysicCollision);

	PreviewMesh = CreateDefaultSubobject<UStaticMeshComponent>("Preview Mesh");
	PreviewMesh->SetupAttachment(GetRootComponent());

	SetReplicates(true);
}

void AToyActor::Grab()
{
	DeactivateAndDestroy();
}

AToyActor* AToyActor::GetToy()
{
	return this;
}

void AToyActor::InitializeToyInfo(const FToyHandle& NewToyInfo)
{
	ToyHandle = NewToyInfo;
}

void AToyActor::ActivateToy()
{
	bActive = true;
	
	OnActivated();
}

void AToyActor::OnActivated_Implementation()
{
	
}

void AToyActor::DeactivateAndDestroy()
{
	bActive = false;
	
	OnDeactivated();
	Destroy();
}

void AToyActor::OnDeactivated_Implementation()
{
	
}
