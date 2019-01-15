// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "DriveableMachineTrack.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class TYPE0PT7_API UDriveableMachineTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	TArray<class AWheelWithSuspension*> GetWheels() const;

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

private:
	UDriveableMachineTrack();

	UPROPERTY(EditDefaultsOnly) float MaxTrackDrivingForce = 10000000; //10,000 kN

private: 
	virtual void BeginPlay() override;

	void DriveTrack(float CurrentThrottle);
};
