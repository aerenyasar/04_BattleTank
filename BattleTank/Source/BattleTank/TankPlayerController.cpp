// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include"Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerPawn = GetControlledTank();
	if (PlayerPawn)
	{
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	FVector LookDirection;
	FVector LookLocation;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
	if (GetLookDirection(ScreenLocation,LookDirection,LookLocation))
	{
		FHitResult Hit;
		if (GetLookVectorHitLocation(LookDirection, LookLocation,Hit))
		{
			OutHitLocation = Hit.Location;
		}

	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection,FVector& LookLocation) const
{
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		LookLocation, 
		LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector Direction,FVector Location,FHitResult &Hit) const
{
	return GetWorld()->LineTraceSingleByChannel(
		Hit,
		Location,
		Location + Direction * LineTraceRange,
		ECollisionChannel::ECC_Visibility
	);
}

ATank *  ATankPlayerController::GetControlledTank() const
{
	
	return Cast<ATank>(GetPawn());
}
