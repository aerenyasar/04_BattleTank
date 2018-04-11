// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void AimTowardsCrosshair();
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection,FVector& LookLocation) const;
	bool GetLookVectorHitLocation(FVector LookDirection,FVector LookLocation,FHitResult &Hit) const;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent * AimCompRef);

private:
	virtual bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333;
	UPROPERTY(EditDefaultsOnly)
	int32 LineTraceRange = 10000;
	UTankAimingComponent* AimingComponent = nullptr;
};
