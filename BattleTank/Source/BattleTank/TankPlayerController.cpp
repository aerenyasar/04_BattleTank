// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


ATank *  ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());

}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlaterController Begin Play"));
	auto PlayerPawn = GetControlledTank();
	if (PlayerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *PlayerPawn->GetName());

	}
}