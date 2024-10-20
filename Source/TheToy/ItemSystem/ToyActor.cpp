// Fill out your copyright notice in the Description page of Project Settings.

#include "ToyActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AToyActor::AToyActor()
{
	PhysicCollision = CreateDefaultSubobject<USphereComponent>("Physic Collision");
	SetRootComponent(PhysicCollision);

	PreviewMesh = CreateDefaultSubobject<UStaticMeshComponent>("Preview Mesh");
	PreviewMesh->SetupAttachment(GetRootComponent());
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Component");
	ProjectileMovement->UpdatedComponent = PhysicCollision;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	SetReplicates(true);
	SetReplicatingMovement(true);
}

void AToyActor::Grab()
{
	if (bActive)
	{
		OnGrab.Broadcast();
	
		DeactivateAndDestroy();
	}
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
