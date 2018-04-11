// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Public/TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetPawn()&&AimingComponent)) { return; }
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
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
			return true;
		}

	}
	return false;
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

