// Fill out your copyright notice in the Description page of Project Settings.
#include "../Public/TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Warning,TEXT("AI Tank %s"),*GetControlledTank()->GetName())
	if (GetPlayerTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("AI found Player %s"), *GetPlayerTank()->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI found no Player"))

	}
}

void ATankAIController::Tick(float DeltaTime)
{
	auto Tank = GetControlledTank();
	if (GetPlayerTank())
	{
		Tank->AimAt(GetPlayerTank()->GetActorLocation());
	}
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn) {
		return Cast<ATank>(PlayerPawn);
	}
	return nullptr;
}

