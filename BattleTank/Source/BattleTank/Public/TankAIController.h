// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "TankAIController.generated.h"

class ATank;
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(EditAnywhere, Category = Setup)
	float AcceptanceRadius = 8000;
private:
	void BeginPlay() override;
	UTankAimingComponent* AimingComponent = nullptr;

	virtual void SetPawn(APawn * InPawn) override;

	UFUNCTION()
	void OnTankDeath(); //DELEGATE METHOD
};
