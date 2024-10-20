// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroToyComponent.h"
#include "ItemSystem/ItemSystemCore.h"
#include "Net/UnrealNetwork.h"

UHeroToyComponent::UHeroToyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UHeroToyComponent::SetupToyComponent()
{
	if (ActiveRow < 0)
	{
		auto TableMap = ToysDataTable->GetRowMap();

		TableMap.GetKeys(AllowedRows);
	
		bCanToggleToy = true;
		bCanToggleToy = true;
		ToggleToy();
	}
}

void UHeroToyComponent::ToggleToy()
{
	ServerToggleToy();
}

void UHeroToyComponent::ServerToggleToy_Implementation()
{
	if (!bCanToggleToy) return;
	
	ActiveRow++;
	
	if (!AllowedRows.IsValidIndex(ActiveRow))
	{
		ActiveRow = 0;
	}

	TakeToyFromTable(ActiveRow);
}

void UHeroToyComponent::TakeToyFromTable(uint8 RowIndex)
{
	if (auto Row = ToysDataTable->FindRow<FToysTableRow>(AllowedRows[RowIndex], ""))
	{
		FToyHandle ToyInfo;
		ToyInfo.ToyActorClass = Row->ToyActorClass;
		ToyInfo.RowName = AllowedRows[RowIndex];
		ToyInfo.Cost = Row->Cost;

		CurrentToy = ToyInfo;
		OnToyChanged.Broadcast(CurrentToy);
	}
}

void UHeroToyComponent::LaunchToy()
{
	ServerLaunchToy();
}

void UHeroToyComponent::ServerLaunchToy_Implementation()
{
	if (!bCanLaunchToy) return;
	
	bCanToggleToy = false;
	bCanLaunchToy = false;

	if (UWorld* World = GetWorld())
	{
		const FRotator SpawnRotation = GetOwner()->GetActorRotation();
		const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector({100.0f, 0.0f, 45.0f});

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SpawnLocation);
		SpawnTransform.SetRotation(FQuat(SpawnRotation));

		if (AToyActor* Toy = World->SpawnActorDeferred<AToyActor>(CurrentToy.ToyActorClass, SpawnTransform, GetOwner(),
		                                                          GetOwner<APawn>(),
		                                                          ESpawnActorCollisionHandlingMethod::AlwaysSpawn))
		{
			LaunchedToy = Toy;
			LaunchedToy->InitializeToyInfo(CurrentToy);
			LaunchedToy->OnGrab.AddUObject(this, &UHeroToyComponent::OnGrabbedToy);
			LaunchedToy->FinishSpawning(SpawnTransform);
			LaunchedToy->ActivateToy();
		}
	}
	
	MulticastLaunchToy();
}

void UHeroToyComponent::MulticastLaunchToy_Implementation()
{
	OnToyLaunched.Broadcast();
}

void UHeroToyComponent::OnGrabbedToy()
{
	bCanToggleToy = true;
	bCanLaunchToy = true;
	TakeToyFromTable(ActiveRow);
	
	if (LaunchedToy)
	{
		LaunchedToy->OnGrab.RemoveAll(this);
		LaunchedToy = nullptr;
	}

	MulticastOnGrabbedToy();
}

void UHeroToyComponent::MulticastOnGrabbedToy_Implementation()
{
	OnToyGrabbed.Broadcast();
}

void UHeroToyComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, CurrentToy);
}

void UHeroToyComponent::OnRep_CurrentToy()
{
	OnToyChanged.Broadcast(CurrentToy);
}
