// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	ATank * GetControlledTank() const;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void AimTowardsCrosshair();
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection,FVector& LookLocation) const;
	bool GetLookVectorHitLocation(FVector LookDirection,FVector LookLocation,FHitResult &Hit) const;


private:
	virtual bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333;
	UPROPERTY(EditAnywhere)
	int32 LineTraceRange = 10000;
};
