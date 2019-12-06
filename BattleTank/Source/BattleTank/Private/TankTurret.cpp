// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "BattleTank.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	// Move the Barrel the right the amount 
	// Given the elevation speed, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RotationChange + RelativeRotation.Yaw;
	SetRelativeRotation(FRotator(0,Rotation, 0));	

}


