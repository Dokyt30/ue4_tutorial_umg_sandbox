// Fill out your copyright notice in the Description page of Project Settings.

#include "StateActorComponent.h"


// Sets default values for this component's properties
UStateActorComponent::UStateActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	InitStateCounter();
	// ...
}


// Called when the game starts
void UStateActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
