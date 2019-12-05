// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{

	if (!Barrel) { return; }



	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectil"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	// Calculate the OutLaunchVelocity
	
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		if (Barrel != nullptr)
		{
			MoveBarrel(AimDirection);
			auto Time = GetWorld()->GetTimeSeconds();
			UE_LOG(LogTemp, Warning, TEXT(" %f: Solution found"), Time);
		}
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT(" %f: No solution found"), Time	);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	// Calculate the difference between the current barrel location, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;
	
	
	Barrel->Elevate(5);

}
