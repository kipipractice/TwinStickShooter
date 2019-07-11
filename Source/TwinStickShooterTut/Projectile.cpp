// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "EnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "HealthComponent.h"


AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(CapsuleComponent) == false) {
		UE_LOG(LogTemp, Warning, TEXT("AProjectile::BeginPlay IsValid(CapsuleComponent) == false"))
	}
	else 
	{
		CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::AProjectile::OnOverlapBegin);
		CapsuleComponent->IgnoreActorWhenMoving(GetOwner(), true);
	}
	if (IsValid(HitParticleSystem) == false) {
		UE_LOG(LogTemp, Warning, TEXT("AProjectile::BeginPlay IsValid(HitParticleSystem) == false"))
	}

}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor)) {
		UHealthComponent* HealthComponent = OtherActor->FindComponentByClass<UHealthComponent>();
		if (IsValid(HealthComponent)) {
			HealthComponent->TakeDamage(Damage);
		}
	}


	if (IsValid(HitParticleSystem)) {
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			HitParticleSystem,
			GetActorTransform()
		);
	}
	Destroy();
}

