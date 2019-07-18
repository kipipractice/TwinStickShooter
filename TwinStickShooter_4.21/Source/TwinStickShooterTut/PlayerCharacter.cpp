#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#include "TwinSticksHUD.h"
#include "TwinStickGameMode.h"
#include "CharacterPlayerController.h"
#include "HealthComponent.h"
#include "PlayerStatsWidget.h"
#include "InputType.h"
#include "CustomMacros.h"




void APlayerCharacter::BeginPlay() {
	Super::BeginPlay();

	SetPlayerRespawnTransform(GetActorTransform());
	
	if (validate(IsValid(HealthComponent)) == false) { return; }

	HealthComponent->OnHealthChanged.AddDynamic(this, &APlayerCharacter::OnHealthChanged);
}


void APlayerCharacter::Tick(float DeltaTime) {
	if (LookAroundDelegate.IsBound()) {
		LookAroundDelegate.Execute();
	}
}


void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (validate(IsValid(PlayerInputComponent)) == false) { return; }

	ACharacterPlayerController* PlayerController = Cast<ACharacterPlayerController>(GetController());
	if (validate(IsValid(PlayerController)) == false) { return; }

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
		UE_LOG(LogTemp, Error, TEXT("APlayerCharacter::SetupPlayerInputComponent Unimplemented Input Scheme"));
	}
}


void APlayerCharacter::SetupMouseInputScheme(UInputComponent* PlayerInputComponent) {
	if (validate(IsValid(PlayerInputComponent)) == false) { return; }

	UE_LOG(LogTemp, Display, TEXT("Setup Mouse Input Scheme"));

	SetMouseEventsEnabled(true);

	LookAroundDelegate.BindDynamic(this, &APlayerCharacter::LookAtMousePosition);
}


void APlayerCharacter::SetupControllerInputScheme(UInputComponent* PlayerInputComponent) {
	if (validate(IsValid(PlayerInputComponent)) == false) { return; }

	UE_LOG(LogTemp, Display, TEXT("Setup Controller Input Scheme"));
	SetMouseEventsEnabled(false);

	LookAroundDelegate.BindDynamic(this, &APlayerCharacter::LookAtInputAxisDirection);

	PlayerInputComponent->BindAxis("LookUp");
	PlayerInputComponent->BindAxis("LookRight");
}


void APlayerCharacter::SetPlayerRespawnTransform(FTransform RespawnTransform) {
	UWorld* World = GetWorld();
	if (validate(IsValid(World)) == false) { return; }

	ATwinStickGameMode* GameMode = Cast<ATwinStickGameMode>(World->GetAuthGameMode());
	if (validate(IsValid(GameMode)) == false) { return; }

	GameMode->SetPlayerRespawnLocation(RespawnTransform);
}


void APlayerCharacter::OnHealthChanged(int Health) {
	if (validate(IsValid(PlayerStatsWidget)) == false) { return; }

	PlayerStatsWidget->SetHealth(Health);
}


void APlayerCharacter::PossessedBy(AController* Controller) {
	Super::PossessedBy(Controller);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (validate(IsValid(PlayerController)) == false) { return; }
	
	ATwinSticksHUD* HUD = Cast<ATwinSticksHUD>(PlayerController->GetHUD());
	if (validate(IsValid(HUD)) == false) { return; }

	PlayerStatsWidget = HUD->GetPlayerStatsWidget();
	if (validate(IsValid(PlayerStatsWidget)) == false) { return; }

	if (validate(IsValid(HealthComponent)) == false) { return; }

	PlayerStatsWidget->SetMaxHealth(HealthComponent->GetMaxHealth());
	PlayerStatsWidget->SetHealth(HealthComponent->GetHealth());
}


void APlayerCharacter::LookAtMousePosition() {
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (validate(IsValid(PlayerController)) == false) { return; }

	float MouseX;
	float MouseY;
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


void APlayerCharacter::Die() {
	Super::Die();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (validate(IsValid(PlayerController)) == false) { return; }

	DisableInput(PlayerController);
	LookAroundDelegate.Unbind();
}


void APlayerCharacter::OnDeathTimerEnd() {
	Super::OnDeathTimerEnd();

	ATwinStickGameMode* GameMode = Cast<ATwinStickGameMode>(GetWorld()->GetAuthGameMode());
	if (validate(IsValid(GameMode)) == false) { return;}

	GameMode->RespawnPlayer();
}


void APlayerCharacter::SetMouseEventsEnabled(bool bEnabled) {
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (validate(IsValid(PlayerController)) == false) { return; }

	PlayerController->bShowMouseCursor = bEnabled;
	PlayerController->bEnableClickEvents = bEnabled;
	PlayerController->bEnableMouseOverEvents = bEnabled;
}