// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToyInterface.h"
#include "GameFramework/Actor.h"
#include "ToyActor.generated.h"

class USphereComponent;

USTRUCT()
struct FToyHandle
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Item")
	int Cost = 0;
};

UCLASS()
class THETOY_API AToyActor : public AActor, public IToyInterface
{
	GENERATED_BODY()

public:
	AToyActor();

	virtual void Grab() override;

	virtual AToyActor* GetToy() override;
	
	void InitializeToyInfo(const FToyHandle& NewToyInfo);
	
	void ActivateToy();

	UFUNCTION(BlueprintNativeEvent, Category = "Toy")
	void OnActivated();
	
	void DeactivateAndDestroy();

	UFUNCTION(BlueprintNativeEvent, Category = "Toy")
	void OnDeactivated();

	bool IsActive() const { return bActive; }
	
	FToyHandle GetToyInfo() const { return ToyHandle; }
	
protected:
	UPROPERTY(EditAnywhere, Category = "Toy")
	TObjectPtr<USphereComponent> PhysicCollision;
	
	UPROPERTY(EditAnywhere, Category = "Toy")
	TObjectPtr<UStaticMeshComponent> PreviewMesh;
	
	UPROPERTY(EditInstanceOnly, Category = "Toy")
	FToyHandle ToyHandle;
	
private:
	UPROPERTY(EditInstanceOnly, Category = "Toy")
	bool bActive = false;
};
