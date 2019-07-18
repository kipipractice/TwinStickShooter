// Fill out your copyright notice in the Description page of Project Settings.


#include "Nexus.h"
#include "Engine/World.h"
#include "HealthComponent.h"
#include "NexusDefenceGameMode.h"

// Sets default values
ANexus::ANexus()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

