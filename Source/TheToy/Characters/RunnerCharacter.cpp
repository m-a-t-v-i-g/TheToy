// Fill out your copyright notice in the Description page of Project Settings.

#include "RunnerCharacter.h"
#include "InteractionComponent.h"
#include "Components/SphereComponent.h"

FName ARunnerCharacter::InteractionComponentName {"InteractionComp"};

ARunnerCharacter::ARunnerCharacter()
{
	InteractionSphere = CreateDefaultSubobject<USphereComponent>("InteractionSphere");
	InteractionSphere->SetupAttachment(GetRootComponent());
	
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(InteractionComponentName);
}
