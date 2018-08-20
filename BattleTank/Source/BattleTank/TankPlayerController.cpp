// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"

#define OUT


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possing the Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Possed: %s"), *(ControlledTank->GetName()));
	}
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
}

// called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Outparameter
	if (GetSigthRayLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString())
			// TODO tell controlled tank to aim at this point
	}
}

// Get world location of linetrace trough crosshai, true if hits landscape
bool ATankPlayerController::GetSigthRayLocation(FVector& OUTHitLocation) const
{
	
	// Find the crosshai position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// "De-project" the position of the crosshair to a world direction
	FVector	LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that, and see what we hit(up to a max range)
		GetLookVectorHitLocation(OUTHitLocation, LookDirection);
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation,FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		OUT CameraWorldLocation,
		OUT LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& HitLocation, FVector LookDirection) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection *LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		OUT HitResult,
		StartLocation,
		EndLocation,
		ECC_Visibility
	))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else
	{
		HitLocation = FVector(0.0);
		return false;
	}
	
}
