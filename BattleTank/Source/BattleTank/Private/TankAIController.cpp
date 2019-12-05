// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerControlledTank = GetPlayerTank();
	if (!PlayerControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController didn't found the Player Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController Found: %s"), *(PlayerControlledTank->GetName()));
	}
	UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"));
}

void ATankAIController::Tick(float DeltaTime)

{
	Super::Tick(DeltaTime);

	if (GetPlayerTank())
	{
		// TODO move towards the player

		// Aim towards the player
		GetAIControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// Fire if ready
		}
}

ATank * ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATank>(PlayerPawn);
}
