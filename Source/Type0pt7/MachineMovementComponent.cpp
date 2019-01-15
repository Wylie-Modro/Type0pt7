// Fill out your copyright notice in the Description page of Project Settings.

#include "MachineMovementComponent.h"
#include "DriveableMachineTrack.h"
	
void UMachineMovementComponent::Initialise(UDriveableMachineTrack* LeftTrackToSet, UDriveableMachineTrack* RightTrackToSet) 
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UMachineMovementComponent::IntendMoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UMachineMovementComponent::IntendMoveRight(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

