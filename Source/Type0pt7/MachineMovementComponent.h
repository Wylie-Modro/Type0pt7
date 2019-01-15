// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "MachineMovementComponent.generated.h"

class UDriveableMachineTrack;

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TYPE0PT7_API UMachineMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public: 
	UFUNCTION(BlueprintCallable, Category = Setup)

	void Initialise(UDriveableMachineTrack* LeftTrackToSet, UDriveableMachineTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Input) 
	void IntendMoveRight(float Throw);

private:
	UDriveableMachineTrack* LeftTrack = nullptr;
	UDriveableMachineTrack* RightTrack = nullptr;

};
