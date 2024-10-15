﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "HeroCharacter.generated.h"

struct FInputActionValue;
class UPlayerInputConfig;

UCLASS()
class THETOY_API AHeroCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AHeroCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Character")
	TObjectPtr<UPlayerInputConfig> InputConfig;
	
	void InputMove(const FInputActionValue& Value);
	void InputLook(const FInputActionValue& Value);
};
