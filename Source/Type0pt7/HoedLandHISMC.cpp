// Fill out your copyright notice in the Description page of Project Settings.

#include "HoedLandHISMC.h"
#include "DriveableMachine.h"

UHoedLandHISMC::UHoedLandHISMC()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHoedLandHISMC::BeginPlay()
{
	Super::BeginPlay();
	//SpawnHoedTiles();
}

void UHoedLandHISMC::SpawnHoedTiles(FVector& Location, FRotator& Rotation)
{
	AddInstance(FTransform(Rotation, Location, FVector(1.f)));
	//AddInstance(FTransform(Location));
}


