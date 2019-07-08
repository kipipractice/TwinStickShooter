// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "EnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


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
	}
	if (IsValid(HitParticleSystem) == false) {
		UE_LOG(LogTemp, Warning, TEXT("AProjectile::BeginPlay IsValid(HitParticleSystem) == false"))
	}
	
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *OtherActor->GetName());
	if (OtherActor->GetInstigator() == GetInstigator()) {
		return;
	}

	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(OtherActor);
	if (IsValid(EnemyCharacter)) {
		EnemyCharacter->TakeDamage(Damage);	
	}
	if (IsValid(HitParticleSystem) && IsValid(OtherActor)) {
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			HitParticleSystem,
			OtherActor->GetActorTransform()
		);
	}
	Destroy();
}

