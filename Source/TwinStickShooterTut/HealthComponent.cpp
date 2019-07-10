// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
	Super::PostEditChangeProperty(PropertyChangedEvent);
	Health = MaxHealth;
}

void UHealthComponent::TakeDamage(float Damage) {
	if (bDead) {
		return;
	}

	Health -= Damage;

	if (Health <= 0) {
		bDead = true;
		OnDeath.Broadcast();
	}
	OnHealthChanged.Broadcast(Health);
}


void UHealthComponent::Heal(float HealingPower) {
	if (bDead) {
		return;
	}

	Health += HealingPower;
	if (Health > MaxHealth) {
		Health = MaxHealth;
	}
	OnHealthChanged.Broadcast(Health);
}


float UHealthComponent::GetHealth() {
	return Health;
}

float UHealthComponent::GetMaxHealth() {
	return MaxHealth;
}

