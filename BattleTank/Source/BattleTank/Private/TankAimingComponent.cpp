// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAimingComponent.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankTurret.h"
#include "../Public/Projectile.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = FPlatformTime::Seconds();
}
void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (AmmoLeft == 0)
	{
		FiringStatus = EFiringState::NoAmmo;
	}
	else if (FPlatformTime::Seconds() - LastFireTime < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringState::Aiming;
	}
	else
	{
		FiringStatus = EFiringState::Locked;
	}
}

void UTankAimingComponent::Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

EFiringState UTankAimingComponent::GetFiringState()
{
	return FiringStatus;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (Barrel->GetForwardVector().Equals(AimDirection,0.01)) { return false; }
	return true;
}

void UTankAimingComponent::Fire()
{
	if (FiringStatus == EFiringState::Reloading|| FiringStatus == EFiringState::NoAmmo) { return; }
	if (!ensure(Barrel&&ProjectileBlueprint)) { return; }
	AmmoLeft--;
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))
		);
	Projectile->LaunchProjectile(LaunchSpeed);
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel&&Turret)) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	TArray<AActor*> ActorIgnoreList;

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		ActorIgnoreList,
		false
	);
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
	}
	return;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto DeltaRotator = AimDirection.Rotation() - Barrel->GetForwardVector().Rotation();
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	auto DeltaRotator = AimDirection.Rotation() - Turret->GetForwardVector().Rotation();
	if (FMath::Abs(DeltaRotator.Yaw) > 180) { DeltaRotator.Yaw*=-1; }
	Turret->Rotate(DeltaRotator.Yaw);
}
