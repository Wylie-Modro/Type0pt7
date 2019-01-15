// Fill out your copyright notice in the Description page of Project Settings.

#include "DriveableMachine.h"

// Sets default values
ADriveableMachine::ADriveableMachine()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADriveableMachine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADriveableMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADriveableMachine::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

