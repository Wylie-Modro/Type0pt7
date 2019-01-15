// Fill out your copyright notice in the Description page of Project Settings.

#include "DriveableMachineTrack.h"
#include "WheelSpawnPoint.h"
#include "WheelWithSuspension.h"

UDriveableMachineTrack::UDriveableMachineTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDriveableMachineTrack::BeginPlay()
{
	Super::BeginPlay();
}

void UDriveableMachineTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

TArray<class AWheelWithSuspension*> UDriveableMachineTrack::GetWheels() const
{
	TArray<AWheelWithSuspension*> Wheels;
	TArray<USceneComponent*> Childern;

	GetChildrenComponents(true, Childern);

	for (USceneComponent* Child : Childern)
	{
		auto SpawnPointChild = Cast<UWheelSpawnPoint>(Child);
		if (!SpawnPointChild) { continue; }

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto WheelWithSuspension = Cast<AWheelWithSuspension>(SpawnedChild);
		if (!WheelWithSuspension) { continue; }
		Wheels.Add(WheelWithSuspension);
	}

	return Wheels;
}

void UDriveableMachineTrack::DriveTrack(float CurrentThrottle)
{
	float Time = GetWorld()->GetTimeSeconds();

	float ForceMagApplied = CurrentThrottle * MaxTrackDrivingForce;
	TArray<AWheelWithSuspension*> Wheels = GetWheels();
	float ForceMagPerWheel = ForceMagApplied / Wheels.Num();
	
	for (AWheelWithSuspension* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForceMagPerWheel);
	}
}



