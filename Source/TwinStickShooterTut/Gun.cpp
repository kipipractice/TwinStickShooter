// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "Components/AudioComponent.h"
#include "Projectile.h"


// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FireSoundComponent = CreateDefaultSubobject<UAudioComponent>("FireAudioComponent");
	FireSoundComponent->bAutoActivate = false;
	FireSoundComponent->AttachTo(GetRootComponent());
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger() {
	// Call Fire because Timer function is called after the delay.
	Fire();

	GetWorld()->GetTimerManager().SetTimer(
		FireTimerHandle,
		this,
		&AGun::Fire,
		1 / GetFireRate(),
		true
	);
}


void AGun::ReleaseTrigger() {
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}


void AGun::Fire() {
	PlayFireSound();
	SpawnProjectile();
}


void AGun::SpawnProjectile() {
	checkf(GunSpawnPosition, TEXT("GunSpawnPosition is not set!"));
	checkf(ProjectileTemplate, TEXT("Projectile template to fire is not set!"));

	AActor* Player = GetWorld()->GetFirstPlayerController()->GetPawn();

	FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
	SpawnParameters.Owner = Player;
	SpawnParameters.Instigator = Player->Instigator;

	FVector GunSpawnLocation = GunSpawnPosition->GetComponentLocation();
	FRotator GunSpawnRotation = FRotator(0, GunSpawnPosition->GetComponentRotation().Yaw, 0);

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileTemplate.Get(),
		GunSpawnLocation,
		GunSpawnRotation,
		SpawnParameters
	);
}


void AGun::PlayFireSound() {
	if ensure(FireSoundComponent)
		FireSoundComponent->Play();
	else
		UE_LOG(LogTemp, Error, TEXT("%s does not have a sound component!"), *GetName());
}

float AGun::GetFireRate() {
	return FireRate;
}