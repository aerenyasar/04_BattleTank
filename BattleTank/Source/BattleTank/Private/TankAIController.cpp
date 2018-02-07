// Fill out your copyright notice in the Description page of Project Settings.
#include "../Public/TankAIController.h"

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
