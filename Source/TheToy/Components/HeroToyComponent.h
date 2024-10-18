// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemSystem/ToyActor.h"
#include "HeroToyComponent.generated.h"

class AToyActor;

DECLARE_MULTICAST_DELEGATE(FOnToyLaunched);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnToyChanged, const FToyHandle&);
DECLARE_MULTICAST_DELEGATE(FOnToyGrabbed);

UCLASS(ClassGroup = "The Toy", meta = (BlueprintSpawnableComponent))
class THETOY_API UHeroToyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHeroToyComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Toy Component")
	TObjectPtr<UDataTable> ToysDataTable;

	FOnToyLaunched OnToyLaunched;
	FOnToyChanged OnToyChanged;
	FOnToyGrabbed OnToyGrabbed;
	
	void SetupToyComponent();
	
	void ToggleToy();

	UFUNCTION(Server, Reliable)
	void ServerToggleToy();
	
	void TakeToyFromTable(uint8 RowIndex);
	
	void LaunchToy();

	UFUNCTION(Server, Reliable)
	void ServerLaunchToy();
	
	UFUNCTION(NetMulticast, Unreliable)
	void MulticastLaunchToy();
	
	void OnGrabbedToy();
	
	UFUNCTION(NetMulticast, Unreliable)
	void MulticastOnGrabbedToy();
	
	FToyHandle GetCurrentToyHandle() const { return CurrentToy; }

protected:
	UPROPERTY(EditInstanceOnly, ReplicatedUsing = "OnRep_CurrentToy", Category = "Toy Component")
	FToyHandle CurrentToy;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_CurrentToy();
	
private:
	UPROPERTY(EditInstanceOnly, Category = "Toy Component")
	TObjectPtr<AToyActor> LaunchedToy;
	
	UPROPERTY(VisibleInstanceOnly, Category = "Toy Component")
	int ActiveRow = -1;
	
	UPROPERTY(EditInstanceOnly, Category = "Toy Component")
	bool bCanToggleToy = true;

	UPROPERTY(EditInstanceOnly, Category = "Toy Component")
	bool bCanLaunchToy = true;

	TArray<FName> AllowedRows;
};
