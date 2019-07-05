// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Projectile.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "DebugPrinter.h"
#include "Runtime/Engine/Classes/Components/AudioComponent.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audion component"));
	//AudioComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

}


void AGun::PullTrigger()
{
	GetWorld()->GetTimerManager().SetTimer(
		FireTimerHandle,
		this,
		&AGun::Fire,
		1 / FireRate,
		true,
		0.0f
	);
}

void AGun::ReleaseTrigger()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);

}

void AGun::Fire() {
	DebugPrinter::Print("Fire");
	if (!ensure(ProjectileSpawnPosition) || !ensure(ProjectileTemplate)) {
		return;
	}
	//checkf(GunSpawnPosition, TEXT("GunSpawnPosition is not set!"));
	//checkf(ProjectileTemplate, TEXT("Projectile template to fire is not set!"));

	AActor* Player = GetWorld()->GetFirstPlayerController()->GetPawn();

	FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
	SpawnParameters.Owner = Player;
	SpawnParameters.Instigator = Player->Instigator;

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileTemplate.Get(), 
		ProjectileSpawnPosition->GetComponentLocation(),
		ProjectileSpawnPosition->GetComponentRotation(),
		SpawnParameters
	);
	/*
	if (AudioComponent) {
		AudioComponent->Play();

	}
	*/
	
}
