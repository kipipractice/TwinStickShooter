// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TwinStickGameMode.h"
#include "NexusDefenceGameMode.generated.h"


class ANexus;
/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTERTUT_API ANexusDefenceGameMode : public ATwinStickGameMode
{
	GENERATED_BODY()

public:
	ANexus* GetNexus();

protected:
	void BeginPlay() override;

	UPROPERTY()
	ANexus* Nexus = nullptr;

	UFUNCTION()
	void SetNexusHealth(int Health);
	
	UFUNCTION()
	void LoseGame();
};
