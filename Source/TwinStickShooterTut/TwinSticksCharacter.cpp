// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinSticksCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Components/AudioComponent.h"

#include "DebugPrinter.h"
#include "Gun.h"
#include "TwinStickGameMode.h"

// Sets default values
ATwinSticksCharacter::ATwinSticksCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DeathSoundComponent = CreateDefaultSubobject<UAudioComponent>("DeathSoundAudioComponent");
	DeathSoundComponent->bAutoActivate = false;

	Health = MaxHealth;
}

// Called when the game starts or when spawned
void ATwinSticksCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (StartingGunTemplate) {
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = this;
		SpawnInfo.Instigator = Instigator;

		Gun = GetWorld()->SpawnActor<AGun>(StartingGunTemplate, SpawnInfo);
		SetGun(Gun);
	}
}

// Called every frame
void ATwinSticksCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATwinSticksCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATwinSticksCharacter::StartFiring);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ATwinSticksCharacter::StopFiring);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATwinSticksCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATwinSticksCharacter::MoveRight);
}


void ATwinSticksCharacter::StartFiring() {
	if (!Gun)
		return;

	Gun->PullTrigger();
}

void ATwinSticksCharacter::StopFiring() {
	if (!Gun)
		return;

	Gun->ReleaseTrigger();
}


void ATwinSticksCharacter::MoveForward(float Value) {
	AddMovementInput(FVector(1, 0, 0), Value);
}


void ATwinSticksCharacter::MoveRight(float Value) {
	AddMovementInput(FVector(0, 1, 0), Value);
}


void ATwinSticksCharacter::TakeDamage(float Damage) {
	if (bDead) {
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Damage %s by %f"), *GetName(), Damage);
	Health -= Damage;
	if (Health <= 0 ? true : false) {
		bDead = true;
		Die();
	}
}


void ATwinSticksCharacter::SetGun(AGun* NewGun) {
	if (CharacterMesh && CharacterMesh->DoesSocketExist("GunSocket")) {
		Gun->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "GunSocket");
	}
	else
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("%s can't attach a gun because socket named 'GunSocket' doesn't exist or there is no mesh!"),
			*GetName()
		);
	}
}


void ATwinSticksCharacter::Die_Implementation() {
	// TODO: Use error debug printer instead.
	checkf(DeathSoundComponent, TEXT("No sound component on %s"), *GetName());

	UE_LOG(LogTemp, Warning, TEXT("Character %s is dead!"), *GetName());

	DeathSoundComponent->Play();
	GetWorld()->GetTimerManager().SetTimer(
		DeathTimerHandle,
		this,
		&ATwinSticksCharacter::OnDeathTimerEnd,
		DeathAnimationTime,
		true
	);

	StopFiring();
}


void ATwinSticksCharacter::OnDeathTimerEnd() {
	Destroy();
}


void ATwinSticksCharacter::LookInDirection(FVector Direction) {
	FRotator Rotation = UKismetMathLibrary::MakeRotFromX(Direction);
	GetController()->SetControlRotation(Rotation);
}


