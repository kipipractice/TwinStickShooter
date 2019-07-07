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

	ACharacterPlayerController* PlayerController = Cast<ACharacterPlayerController>(GetController());
	if (PlayerController) {
		checkf(PlayerInputComponent, TEXT("Player Input Component not found!"));
		ControllerInputType = PlayerController->GetInputType();
		if (ControllerInputType == InputType::PC) {
			UE_LOG(LogTemp, Warning, TEXT("Setup input type for PC!"));

			LookAroundDelegate.BindDynamic(this, &APlayerCharacter::LookAtMousePosition);

			PlayerController->bShowMouseCursor = true;
			PlayerController->bEnableClickEvents = true;
			PlayerController->bEnableMouseOverEvents = true;
		}
		else if (ControllerInputType == InputType::Controller)
		{
			UE_LOG(LogTemp, Warning, TEXT("Setup input type for Controller!"));

			LookAroundDelegate.BindDynamic(this, &APlayerCharacter::LookAtInputAxisDirection);

			PlayerInputComponent->BindAxis("LookUp");
			PlayerInputComponent->BindAxis("LookRight");

			PlayerController->bShowMouseCursor = false;
			PlayerController->bEnableClickEvents = false;
			PlayerController->bEnableMouseOverEvents = false;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Unknown input type detected!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Wrong type of controller possesed player controlled character!"))
	}
}


void APlayerCharacter::TakeDamage(float Damage) {
	Super::TakeDamage(Damage);

	if (ensure(HUD)) {
		HUD->SetHealth(Health);
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
			// TODO: Change when updated version of debug printer with error logging is available.
			UE_LOG(LogTemp, Error, TEXT("Player Character doesn't have a controller with a TwinSticksHUD"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Initialized PlayerCharacter without a PlayerController"));
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
		PlayerController->SetControlRotation(LookAtRotation);
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
		UE_LOG(LogTemp, Warning, TEXT("Disable input from player!"));
		DisableInput(PlayerController);
	}

	LookAroundDelegate.Unbind();
}


void APlayerCharacter::OnDeathTimerEnd() {
	Super::OnDeathTimerEnd();

	ATwinStickGameMode* GameMode = Cast<ATwinStickGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->RespawnPlayer();
}