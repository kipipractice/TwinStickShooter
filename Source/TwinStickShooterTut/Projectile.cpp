// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "DebugPrinter.h"
#include "EnemyCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile movement component"));

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (!CapsuleComponent) {
		DebugPrinter::Print("Projectile capsule component not set");
	}
	else {
		CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::AProjectile::OnOverlapBegin);
	}
	
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// do not do anything when overlapping with the player
	if (OtherActor == GetOwner()) {
		return;
	}
	//DebugPrinter::Print("projectile overlapping");
	AEnemyCharacter* EnemyCharacter = dynamic_cast<AEnemyCharacter*>(OtherActor);
	if (EnemyCharacter) {
		EnemyCharacter->TakeDamage(Damage);
		/*
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			HitParticleEmitter,
			EnemyCharacter->GetActorLocation());

		*/

		// TODO: sshe opravime po kusno.
		Destroy();
	}
}

