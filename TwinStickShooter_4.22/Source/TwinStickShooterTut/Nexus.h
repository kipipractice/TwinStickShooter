// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Nexus.generated.h"

class UHealthComponent;

UCLASS()
class TWINSTICKSHOOTERTUT_API ANexus : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANexus();

protected:

	UPROPERTY(EditDefaultsOnly, Instanced)
	UHealthComponent* HealthComponent;

};
