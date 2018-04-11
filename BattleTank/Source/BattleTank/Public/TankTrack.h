// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float Throttle);
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce =400000; //40 ton tank 10 m/s2 acc
private:
	virtual void BeginPlay() override;
	UTankTrack();
	void ApplySidewaysForce();
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	void DriveTrack();
	float CurrentThrottle = 0;
};
