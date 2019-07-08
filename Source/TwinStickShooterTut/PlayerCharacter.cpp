// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#include "TwinSticksHUD.h"
#include "TwinStickGameMode.h"
#include "CharacterPlayerController.h"
#include "InputType.h"
#include "DebugPrinter.h"




APlayerCharacter::APlayerCharacter() {

}


void APlayerCharacter::BeginPlay() {
	Super::BeginPlay();

	ATwinStickGameMode* GameMode = Cast<ATwinStickGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->SetPlayerRespawnLocation(GetActorTransform());
}


void APlayerCharacter::Tick(float DeltaTime) {
	if (LookAroundDelegate.IsBound()) {
		LookAroundDelegate.Execute();
	}
}


void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!PlayerInputComponent)
		return;

	ACharacterPlayerController* PlayerController = Cast<ACharacterPlayerController>(GetController());
	if (PlayerController) {
		ControllerInputType = PlayerController->GetInputType();
		if (ControllerInputType == InputType::PC) {
			SetupMouseInputScheme(InputComponent);
		}
		else if (ControllerInputType == InputType::Controller)
		{
			SetupControllerInputScheme(InputComponent);
		}
		else
		{
			unimplemented();
		}
	}
	else
	{
		DebugPrinter::Print("Wrong type of controller possesed PlayerCharacter!", EMessageType::Error);
	}
}


void APlayerCharacter::SetupMouseInputScheme(UInputComponent* PlayerInputComponent) {
	DebugPrinter::Print("Setup PC scheme!");

	SetMouseEventsEnabled(true);

	LookAroundDelegate.BindDynamic(this, &APlayerCharacter::LookAtMousePosition);
}


void APlayerCharacter::SetupControllerInputScheme(UInputComponent* PlayerInputComponent) {
	DebugPrinter::Print("Setup controller scheme!");

	SetMouseEventsEnabled(false);

	LookAroundDelegate.BindDynamic(this, &APlayerCharacter::LookAtInputAxisDirection);

	PlayerInputComponent->BindAxis("LookUp");
	PlayerInputComponent->BindAxis("LookRight");
}


void APlayerCharacter::TakeDamage(float Damage) {
	Super::TakeDamage(Damage);

	if (ensure(HUD)) {
		HUD->SetHealth(Health);
	}
	else
	{
		DebugPrinter::Print("No HUD for PlayerCharacter!", EMessageType::Error);
	}
}


void APlayerCharacter::PossessedBy(AController* Controller) {
	Super::PossessedBy(Controller);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController) {
		HUD = Cast<ATwinSticksHUD>(PlayerController->GetHUD());
		if (ensure(HUD)) {
			HUD->SetMaxHealth(MaxHealth);
			HUD->SetHealth(Health);
		}
		else
		{
			DebugPrinter::Print("Player Character doesn't have a controller with a TwinSticksHUD", EMessageType::Error);
		}
	}
	else
	{
		DebugPrinter::Print("Initialized PlayerCharacter without a PlayerController", EMessageType::Warning);
	}
}


void APlayerCharacter::LookAtMousePosition() {
	float MouseX;
	float MouseY;
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	PlayerController->GetMousePosition(MouseX, MouseY);
	FVector2D MousePosition = FVector2D(MouseX, MouseY);
	FHitResult HitResult;
	if (PlayerController->GetHitResultAtScreenPosition(MousePosition, ECC_Visibility, false, HitResult)) {
		FVector Location = HitResult.Location;
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Location);
		PlayerController->SetControlRotation(FRotator(0, LookAtRotation.Yaw, 0));
	}
}


void APlayerCharacter::LookAtInputAxisDirection() {
	float X = InputComponent->GetAxisValue("LookUp");
	float Y = InputComponent->GetAxisValue("LookRight");

	FVector Direction = FVector(X, Y, 0);

	if (Direction.Size() > InputDeadZone) {
		LookInDirection(Direction);
	}
}


void APlayerCharacter::Die_Implementation() {
	Super::Die_Implementation();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController) {
		DisableInput(PlayerController);
	}

	LookAroundDelegate.Unbind();
}


void APlayerCharacter::OnDeathTimerEnd() {
	Super::OnDeathTimerEnd();

	ATwinStickGameMode* GameMode = Cast<ATwinStickGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->RespawnPlayer();
}


void APlayerCharacter::SetMouseEventsEnabled(bool bEnabled) {
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	checkf(PlayerController, TEXT("Player is not controlled by APlayerController!"));

	PlayerController->bShowMouseCursor = bEnabled;
	PlayerController->bEnableClickEvents = bEnabled;
	PlayerController->bEnableMouseOverEvents = bEnabled;
}