// Fill out your copyright notice in the Description page of Project Settings.
#include "../Public/TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());
	if (PlayerTank)
	{
		Cast<ATank>(GetPawn())->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
	}

}
