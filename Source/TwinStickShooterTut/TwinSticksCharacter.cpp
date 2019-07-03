// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinSticksCharacter.h"
#include "Gun.h"
#include "Components/InputComponent.h"

// Sets default values
ATwinSticksCharacter::ATwinSticksCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = MaxHealth;
}

// Called when the game starts or when spawned
void ATwinSticksCharacter::BeginPlay()
{
	Super::BeginPlay();
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
	
	// PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATwinSticksCharacter::FireGun);

}

/*
void ATwinSticksCharacter::FireGun() {
	checkf(Gun != nullptr, TEXT("TwinSticksCharacter needs a reference to a gun!"))
	Gun->Fire();
}
*/

bool ATwinSticksCharacter::IsDead() {
	return Health <= 0 ? true : false;
}

void ATwinSticksCharacter::TakeDamage(float Damage) {
	UE_LOG(LogTemp, Warning, TEXT("Damage %s by %f"), *GetName(), Damage);
	Health -= Damage;
	if (IsDead()) {
		bDead = true;
	}
}
