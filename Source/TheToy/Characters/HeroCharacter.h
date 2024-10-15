// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "HeroCharacter.generated.h"

struct FInputActionValue;
class UCameraComponent;
class UPlayerInputConfig;
class UHeroToyComponent;

UCLASS()
class THETOY_API AHeroCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AHeroCharacter();

	static FName ToyComponentName;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Character")
	TObjectPtr<UPlayerInputConfig> InputConfig;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	TObjectPtr<UHeroToyComponent> ToyComponent;
	
	void InputMove(const FInputActionValue& Value);
	void InputLook(const FInputActionValue& Value);
};
